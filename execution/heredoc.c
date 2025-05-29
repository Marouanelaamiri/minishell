/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:13:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/25 23:53:34 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_heredoc_line(int *fds, t_heredoc *heredoc)
{
	char	*line;
	char	*l_dup;

	line = readline("> ");
	if (!line)
	{
		if (!ttyname(0))
		{
			if (open("/dev/tty", O_RDONLY) == -1)
				return (-1);
			return (g_sig = 1, -1);
		}
		return (-1);
	}
	l_dup = ft_strdup_gc(line);
	if (!l_dup)
		return (free(line), close(fds[0]), close(fds[1]), -1);
	free(line);
	if (ft_strcmp(l_dup, heredoc->delim) == 0)
		return (1);
	if (!heredoc->quoted)
		starboy_expand_heredoc(&l_dup, heredoc->env);
	write(fds[1], l_dup, ft_strlen(l_dup));
	write(fds[1], "\n", 1);
	return (0);
}

int	heredoc_pipe(const char *delim, t_env *env, int quoted)
{
	int					fds[2];
	int					status;
	t_heredoc			heredoc;

	heredoc.delim = delim;
	heredoc.env = env;
	heredoc.quoted = quoted;
	g_sig = 0;
	ft_update_exit_status(0, 63);
	if (pipe(fds) < 0)
		return (perror("pipe"), 1);
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		status = handle_heredoc_line(fds, &heredoc);
		ft_update_exit_status(1, 63);
		if (status != 0)
			break ;
	}
	close(fds[1]);
	signal(SIGINT, ft_ctre_c);
	return (fds[0]);
}

static int	count_heredocs(t_cmd *cmd_list)
{
	int		count;
	t_redir	*redir;

	count = 0;
	while (cmd_list)
	{
		redir = cmd_list->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				count++;
				if (count > 16)
					return (-1);
			}
			redir = redir->next;
		}
		cmd_list = cmd_list->next;
	}
	return (count);
}

static int	handle_heredoc(t_redir *redir, t_env *env)
{
	int	fd;

	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			fd = heredoc_pipe(redir->value, env, redir->quoted);
			if (fd == -1)
				return (-1);
			else if (g_sig == 1)
				return (-1);
			if (fd == -2)
			{
				ft_update_exit_status(130, 63);
				return (-1);
			}
			redir->fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}

int	preprocess_heredocs(t_cmd *cmd_list, t_env *env)
{
	if (count_heredocs(cmd_list) < 0)
	{
		print_error ("heredoc", "maximum here-document count exceeded");
		ft_update_exit_status(2, 63);
		exit(2);
	}
	while (cmd_list)
	{
		if (handle_heredoc(cmd_list->redir, env) == -1)
			return (-1);
		cmd_list = cmd_list->next;
	}
	return (0);
}
