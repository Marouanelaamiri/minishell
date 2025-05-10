/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:13:40 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/10 12:41:53 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_export(t_cmd *cmd, t_env **env)
{
    t_token *token    = cmd->args->next;
    int       status = 0;

    if (!token)
        return print_export_list(*env);

    while (token)
    {
        if (handle_one_export(token->value, env))
            status = 1;
        token = token->next;
    }
    return status;
}
int handle_one_export(const char *arg, t_env **env)
{
    char *copy = ft_strdup(arg);
    int   err  = 0;

    if (!copy)
        return 1;
    if (ft_strstr(copy, "+="))
        err = apply_append(copy, env);
    else
        err = apply_assign(copy, env);
    free(copy);
    return err;
}
int apply_assign(char *copy, t_env **env)
{
	char *eq = ft_strchr(copy, '=');
	char *name = NULL;
	char *value = NULL;

	if (eq)
	{
		name = ft_strndup(copy, eq - copy);
		value = ft_strdup(eq + 1);
		if (!name || !value)
			return (free(name), free(value), 1);
		if (!is_valid_id(name))
		{
			print_error(name, "not a valid identifier");
			return (free(name), free(value), 1);
		}
		env_set(env, name, value);
		return (free(name), free(value), 0);
	}
	else
	{
		name = ft_strdup(copy);
		if (!name)
			return 1;
		if (!is_valid_id(name))
		{
			print_error(name, "not a valid identifier");
			return (free(name), 1);
		}
		if (!ft_getenv(*env, name))
			env_set(env, name, NULL);
		return (free(name), 0);
	}
}
int apply_append(char *copy, t_env **env)
{
    char *pos = ft_strstr(copy, "+=");
    char *name;
    char *value;
    char *old;
    char *combined;

    if (!pos)
        return 1;
    name = ft_strndup(copy, pos - copy); 
    value = ft_strdup(pos + 2);
    if (!name || !value)
        return (free(name), free(value), 1);
    if (!is_valid_id(name))
    {
        print_error(name, "not a valid identifier");
        return (free(name), free(value), 1);
    }
    old = ft_getenv(*env, name);
    if (!old)
        old = "";
    combined = ft_strjoin(old, value);
    if (!combined)
        return (free(name), free(value), 1);
    env_set(env, name, combined);
    return (free(name), free(value), free(combined), 0);
}
