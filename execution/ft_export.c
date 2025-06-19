/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:13:40 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/17 12:44:58 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_cmd *cmd, t_env **env)
{
	t_token	*token;
	int		status;

	token = cmd->args->next;
	status = 0;
	if (!token)
		return (print_export_list(*env));
	while (token)
	{
		if (handle_one_export(token->value, env))
			status = 1;
		token = token->next;
	}
	return (status);
}

int	handle_one_export(const char *arg, t_env **env)
{
	char	*copy;
	char	*eq;
	int		err;

	copy = ft_strdup(arg);
	err = 0;
	if (!copy)
		return (1);
	eq = ft_strchr(copy, '=');
	if (eq && eq > copy && *(eq - 1) == '+')
		err = apply_append(copy, env);
	else
		err = apply_assign(copy, env);
	free(copy);
	return (err);
}

static int	process_assignment(char *copy, char *eq, t_env **env)
{
	char	*name;
	char	*value;

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

int	apply_assign(char *copy, t_env **env)
{
	char	*eq;
	char	*name;

	eq = ft_strchr(copy, '=');
	name = NULL;
	if (eq)
		return (process_assignment(copy, eq, env));
	else
	{
		name = ft_strdup(copy);
		if (!name)
			return (1);
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

int	apply_append(char *copy, t_env **env)
{
	char	*pos;
	char	*name;
	char	*value;
	char	*old;
	char	*combined;

	pos = ft_strchr(copy, '=');
	if (!pos || pos == copy || *(pos - 1) != '+')
		return (1);
	name = ft_strndup(copy, (pos - copy) - 1);
	value = ft_strdup(pos + 1);
	if (!name || !value)
		return (free(name), free(value), 1);
	if (!is_valid_id(name))
		return ((print_error(name, "not a valid identifier"),
				free(name), free(value), 1));
	old = ft_getenv(*env, name);
	if (!old)
		old = "";
	combined = ft_strjoin(old, value);
	if (!combined)
		return (free(name), free(value), 1);
	env_set(env, name, combined);
	return (free(name), free(value), free(combined), 0);
}
