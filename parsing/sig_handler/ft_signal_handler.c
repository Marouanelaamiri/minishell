/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:26:31 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/25 23:55:59 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_ctre_c(int sig)
{
	(void)sig;
	while (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_ctre_c);
	signal(SIGQUIT, SIG_IGN);
}
