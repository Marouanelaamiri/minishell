/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/21 12:54:29 by malaamir         ###   ########.fr       */
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

    if (strcmp(name, "echo") == 0)
		return ft_echo(cmd, env);
    if (strcmp(name, "cd") == 0)
		return ft_cd(cmd, env);
    if (strcmp(name, "pwd") == 0)
		return ft_pwd(cmd, env);
    if (strcmp(name, "env") == 0)
		return ft_env(cmd, env);
    if (strcmp(name, "export") == 0)
		return ft_export(cmd, env);
    if (strcmp(name, "unset") == 0)
		return ft_unset(cmd, env);
    if (strcmp(name, "exit") == 0)
		return ft_exit(cmd, env);
    return -1;
}