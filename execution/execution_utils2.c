/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:06:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/12 14:30:38 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_redirection(t_redir *redir, bool *process)
{
	int	fd;

	*process = true;
	if (redir->type == REDIR_IN)
		fd = open(redir->value, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
		fd = redir->fd;
	else
	{
		*process = false;
		fd = -1;
	}
	return (fd);
}

static int	apply_redirection(t_redir *redir, int fd)
{
	if (fd < 0)
	{
		write(2, "minishell ", 10);
		perror(redir->value);
		return (1);
	}
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;
	bool	process;

	redir = cmd->redir;
	while (redir)
	{
		fd = open_redirection(redir, &process);
		if (process)
		{
			if (apply_redirection(redir, fd))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

int	count_cmds(t_cmd *cmd_list)
{
	int	n;

	n = 0;
	while (cmd_list)
	{
		n++;
		cmd_list = cmd_list->next;
	}
	return (n);
}
