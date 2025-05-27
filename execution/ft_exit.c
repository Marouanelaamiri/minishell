/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:59:58 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/27 11:18:24 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_cmd *cmd, t_env **env)
{
	t_token		*arg;
	long long	status;

	(void)env;
	arg = cmd->args->next;
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	if (!arg)
		exit (ft_update_exit_status(0, 0));
	if (!ft_isllnum(arg->value))
	{
		ft_update_exit_status(255, 63);
		print_error("exit: numeric argument required", arg->value);
		exit(255);
	}
	if (arg->next)
	{
		ft_update_exit_status(1, 63);
		return (write (2, "minishell : exit: too many arguments\n", 38), 1);
	}
	status = ft_atoll(arg->value);
	status = status % 256;
	ft_update_exit_status(status, 63);
	exit ((unsigned int)status);
}
