/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:13:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/25 17:34:26 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_pipe(const char *delim, t_env *env, int quoted)
{
	int		fds[2];
	pid_t	pid;
	int		wstatus;

	if (pipe(fds) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fds[0]), close(fds[1]), 1);
	if (pid == 0)
		handle_child(delim, env, fds, quoted);
	close(fds[1]);
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		close(fds[0]);
		g_exit_status = 130;
		return (-2);
	}
	if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0)
		return (close (fds[0]), -1);
	g_exit_status = 0;
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
		print_error ("heredoc", "maximum here-document count exceeded");
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
