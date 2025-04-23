/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/23 17:44:18 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(t_cmd *cmd)
{
	if (cmd->args->type == WORD)
	{
		if (ft_strcmp(cmd->args->value, "echo") == 0)
			return (1);
		if (ft_strcmp(cmd->args->value, "cd") == 0)
			return (1);
		if (ft_strcmp(cmd->args->value, "pwd") == 0)
			return (1);
		if (ft_strcmp(cmd->args->value, "env") == 0)
			return (1);
		if (ft_strcmp(cmd->args->value, "export") == 0)
			return (1);
		if (ft_strcmp(cmd->args->value, "unset") == 0)
			return (1);
		if (ft_strcmp(cmd->args->value, "exit") == 0)
			return (1);
	}
	return (0);

}
int handle_builtins(t_cmd *cmd, t_env **env)
{
    char *name = cmd->args->value;
	int status = 0;

    if (strcmp(name, "echo") == 0)
		status = ft_echo(cmd, env);
    else if (strcmp(name, "cd") == 0)
		status = ft_cd(cmd, env);
    else if (strcmp(name, "pwd") == 0)
		status = ft_pwd(cmd, env);
    else if (strcmp(name, "env") == 0)
		status = ft_env(cmd, env);
    else if (strcmp(name, "export") == 0)
		status = ft_export(cmd, env);
    else if (strcmp(name, "unset") == 0)
		status = ft_unset(cmd, env);
    else if (strcmp(name, "exit") == 0)
		status = ft_exit(cmd, env);
	else	
    	return -1;
	ft_update_exit_status(status);
	return (status);
}
int is_valid_id(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
