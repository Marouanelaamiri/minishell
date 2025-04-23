/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:44 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/23 15:29:42 by malaamir         ###   ########.fr       */
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

char	*ft_strtok(char *str, const char *sep)
{
    static char *next;
    char *start;

    if (str)
        next = str;
    if (!next)
        return NULL;
    while (*next && ft_strchr(sep, *next))
        next++;
    if (*next == '\0')
	{
        next = NULL;
        return NULL;
    }
    start = next;
    while (*next && !ft_strchr(sep, *next))
        next++;
    if (*next) 
	{
        *next = '\0';
        next++;
    } 
	else 
        next = NULL;
    
    return start;
}

int  cd_walk_path(const char *path)
{
    char *dup = ft_strdup(path);
    char *seg;
    int   ret = 0;

    if (!dup)
        return -1;
    seg = ft_strtok(dup, "/");
    while (seg)
    {
        if (ft_strcmp(seg, "..") == 0)
        {
            if (chdir("..") < 0)
            {
                ret = -1;
                break;
            }
        }
        else if (seg[0] != '\0' && ft_strcmp(seg, ".") != 0)
        {
            if (chdir(seg) < 0)
            {
                ret = -1;
                break;
            }
        }
        seg = ft_strtok(NULL, "/");
    }

    free(dup);
    return ret;
}
