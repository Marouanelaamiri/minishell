/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/22 14:55:56 by malaamir         ###   ########.fr       */
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
char *strip_quotes(const char *s)
{
	size_t len = ft_strlen(s);
	if (len >= 2 && (((s[0]) == '"' && s[len - 1 ] == '"') || (s[0]== '\'' && s[len - 1] == '\'')))
	{
		return (ft_strndup(s + 1, len - 2));
	}
	return (ft_strdup(s));
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
