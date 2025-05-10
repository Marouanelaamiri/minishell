/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:13:16 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/10 12:13:56 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_pipe(const char *delim)
{
	int fds[2];
	char *line;

	if (pipe(fds) < 0)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	close(fds[1]);
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
int preprocess_heredocs(t_cmd *cmd_list)
{
    t_redir *redir;

    if (count_heredocs(cmd_list) < 0)
    {
		print_error ("heredoc","minishell: maximum here-document count exceeded" );
        exit(2);
    }
    while (cmd_list)
    {
        redir = cmd_list->redir;
        while (redir)
        {
            if (redir->type == HEREDOC)
            {
                redir->fd = heredoc_pipe(redir->value);
                if (redir->fd < 0)
                    return (-1);
            }
            redir = redir->next;
        }
        cmd_list = cmd_list->next;
    }
    return (0);
}
