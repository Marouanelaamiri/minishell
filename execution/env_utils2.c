/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:48:18 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 12:08:38 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*handel_null_env(t_env	*head)
{
	char	*pwd;
	char	*val;

	head = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd"), exit(1), NULL);
	val = ft_strjoin("PWD=", pwd);
	handle_one_export("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.",
		&head);
	handle_one_export(val, &head);
	handle_one_export("_=/usr/bin/env", &head);
	return (head);
}

t_env	*append_env_node(t_env *head, t_env **tail, char *env)
{
	t_env	*new_node;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return (head);
	new_node = malloc(sizeof *(new_node));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strndup(env, equal_sign - env);
	new_node->value = ft_strdup(equal_sign + 1);
	new_node->next = NULL;
	if (!head)
		head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
	return (head);
}

int	update_existing_env(t_env *env, const char *name,
				const char *value)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->value);
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = NULL;
			return (0);
		}
		env = env->next;
	}
	return (1);
}
