/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:26:31 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/14 14:12:59 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void ft_ctre_c(int sig)
{
	(void)sig;
	write(1, "\n", 1); // Print a newline
	rl_on_new_line(); // Move to a new line
	rl_replace_line("", 0); // Clear the current line
	rl_redisplay(); // Redisplay the prompt
}

void ft_signal_handler(void)
{

	rl_catch_signals = 0; // Catch SIGINT
	signal(SIGINT, ft_ctre_c); // Handle Ctrl+C
	signal(SIGQUIT, SIG_IGN);//  Ignore Ctrl+\ (SIGQUIT)
}