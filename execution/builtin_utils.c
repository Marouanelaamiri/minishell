/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:20:41 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/26 16:17:26 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args)
		return (0);
	if (cmd->args->type != WORD || !cmd->args->value)
		return (0);
	else if (cmd->args->type == WORD)
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

int	handle_builtins(t_cmd *cmd, t_env **env)
{
	int	status;

	status = 0;
	if (!cmd || !cmd->args || !cmd->args->value)
		return (-1);
	if (ft_strcmp(cmd->args->value, "echo") == 0)
		status = ft_echo(cmd, env);
	else if (ft_strcmp(cmd->args->value, "cd") == 0)
		status = ft_cd(cmd, env);
	else if (ft_strcmp(cmd->args->value, "pwd") == 0)
		status = ft_pwd(cmd, env);
	else if (ft_strcmp(cmd->args->value, "env") == 0)
		status = ft_env(cmd, env);
	else if (ft_strcmp(cmd->args->value, "export") == 0)
		status = ft_export(cmd, env);
	else if (ft_strcmp(cmd->args->value, "unset") == 0)
		status = ft_unset(cmd, env);
	else if (ft_strcmp(cmd->args->value, "exit") == 0)
		status = ft_exit(cmd, env);
	else
		return (-1);
	ft_update_exit_status(status, 63);
	return (status);
}

int	is_valid_id(const char *str)
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

void	print_error(const char *cmd, const char *msg)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
