/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:13:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/24 21:45:53 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_heredoc_line(int *fds, t_heredoc *heredoc)
{
	char	*line;

	line = readline("> ");
	if (g_exit_status == 1)
	{
		free(line);
		close(fds[0]);
		close(fds[1]);
		return (-2);
	}
	if (!line)
		return (1);
	if (ft_strcmp(line, heredoc->delim) == 0)
		return (free(line), 1);
	if (!heredoc->quoted)
		starboy_expand_heredoc(&line, heredoc->env);
	write(fds[1], line, ft_strlen(line));
	write(fds[1], "\n", 1);
	free(line);
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
	g_exit_status = 0;
	if (pipe(fds) < 0)
		return (perror("pipe"), 1);
	setup_signal();
	while (1)
	{
		status = handle_heredoc_line(fds, &heredoc);
		if (status != 0)
			break ;
	}
	if (status == -2)
		return (-2);
	close(fds[1]);
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
			if (fd == -2)
			{
				g_exit_status = 1;
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
		print_error ("", "maximum here-document count exceeded");
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
