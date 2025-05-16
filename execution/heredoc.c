/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:13:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/16 22:10:59 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_pipe(const char *delim)
{
	int					fds[2];
	char				*line;
	struct sigaction	sa_old;

	g_exit_status = 0;
	if (pipe(fds) < 0)
		return (perror("pipe"), 1);
	setup_signal(&sa_old);
	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			free(line);
			close(fds[0]);
			close(fds[1]);
			sigaction(SIGINT, &sa_old, NULL);
			return (-2);
		}
		if (!handle_line(line, delim, fds[1]))
			break;
	}
	close(fds[1]);
	sigaction(SIGINT, &sa_old, NULL);
	return (fds[0]);
}

static int count_heredocs(t_cmd *cmd_list)
{
    int       count = 0;
    t_redir  *redir;

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

static int	handle_heredoc(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			fd = heredoc_pipe(redir->value);
			if (fd == -1)
				return (-1);
			if (fd == -2)
			{
				g_exit_status = 130;
				return (-1);
			}
			redir->fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}

int	preprocess_heredocs(t_cmd *cmd_list)
{
	if (count_heredocs(cmd_list) < 0)
	{
		print_error("","maximum here-document count exceeded");
		exit(2);
	}
	while (cmd_list)
	{
		if (handle_heredoc(cmd_list->redir) == -1)
			return (-1);
		cmd_list = cmd_list->next;
	}
	return (0);
}
