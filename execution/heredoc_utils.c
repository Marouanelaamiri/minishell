/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:03:37 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/25 17:04:13 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 1;
	write(1, "\n", 1);
	rl_done = 1;
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

int	handle_line(char *line, const char *delim, int pipe_fd)
{
	if (!line)
		return (0);
	if (ft_strcmp(line, delim) == 0)
	{
		free(line);
		return (0);
	}
	write(pipe_fd, line, ft_strlen(line));
	write(pipe_fd, "\n", 1);
	free(line);
	return (1);
}

void install_heredoc_signals(struct sigaction *oldint,
						struct sigaction *oldquit)
{
    struct sigaction sa;

    sa.sa_handler = heredoc_sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, oldint);
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGQUIT, &sa, oldquit);
}

void restore_signals(const struct sigaction *oldint,
                        const struct sigaction *oldquit)
{
    sigaction(SIGINT, oldint, NULL);
    sigaction(SIGQUIT, oldquit, NULL);
}

void close_pipe_ends(int fds[2])
{
    close(fds[0]);
    close(fds[1]);
}
