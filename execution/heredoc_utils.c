/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:03:37 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/25 17:34:34 by malaamir         ###   ########.fr       */
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

static void	child_heredoc_loop(const char *delim, t_env *env,
								int fd, int quoted)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (g_exit_status == 1)
			exit(130);
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			exit(0);
		}
		if (!quoted)
			starboy_expand_heredoc(&line, env);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_child(const char *delim, t_env *env, int *fds, int quoted)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	close(fds[0]);
	child_heredoc_loop(delim, env, fds[1], quoted);
	return (0);
}
