/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:59:58 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/21 16:54:23 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_cmd *cmd, t_env **env)
{
	t_token		*arg;
	long long	status;

	(void)env;
	arg = cmd->args->next;
	write(1, "exit\n", 5);
	if (!arg)
		exit(g_exit_status);
	if (!ft_isllnum(arg->value))
	{
		print_error("minishell: exit: numeric argument required\n", arg->value);
		exit(255);
	}
	if (arg->next)
		return (print_error("minishell: exit: too many arguments\n",
				arg->value), 1);
	status = ft_atoll(arg->value);
	status = (status % 256);
	exit((unsigned char)status);
}
