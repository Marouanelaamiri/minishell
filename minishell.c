/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:48:53 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/19 23:37:00 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_update_exit_status(0, 63);
		return (1);
	}
	env = init_env(envp);
	env_unset(&env, "OLDPWD");
	update_shell_level(&env);
	ft_signal_handler();
	while (handle_one_line(&env))
		;
	ft_free_env(env);
	return (ft_update_exit_status(0, 63));
}
