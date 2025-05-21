/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:03:37 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/21 17:44:50 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_done = 1;
}

void	setup_signal(struct sigaction *sa_old)
{
	struct sigaction	sa_new;

	sa_new.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, sa_old);
}

void	print_eof_warning(const char *delim)
{
	write(2,
		"minishell: warning: here-document delimited by end-of-file \
(wanted `", 69);
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
}

int	handle_line(char *line, const char *delim, int write_fd)
{
	if (!line)
	{
		print_eof_warning(delim);
		return (0);
	}
	if (ft_strcmp(line, delim) == 0)
	{
		free(line);
		return (0);
	}
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
	return (1);
}
