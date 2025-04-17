/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:52 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/17 15:03:27 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_builtins(t_cmd *cmd, t_env **env)
{
    char *name = cmd->args->value;

    if (strcmp(name, "echo") == 0)   return ft_echo(cmd, env);
    if (strcmp(name, "cd") == 0)     return ft_cd(cmd, env);
    if (strcmp(name, "pwd") == 0)    return ft_pwd(cmd, env);
    if (strcmp(name, "env") == 0)    return ft_env(cmd, env);
    if (strcmp(name, "export") == 0) return ft_export(cmd, env);
    if (strcmp(name, "unset") == 0)  return ft_unset(cmd, env);
    if (strcmp(name, "exit") == 0)   return ft_exit(cmd, env);
    return -1;
}
