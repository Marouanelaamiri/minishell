/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:32:18 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/21 15:33:09 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *init_env(char **envp)
{
	t_env *head = NULL;
	t_env *tail = NULL;
	t_env *new_node;
	int i = 0;
	char *equal_sign;

	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			new_node = malloc(sizeof *(new_node));
			if (!new_node)
				return (NULL);
			new_node->name = ft_strndup(envp[i], equal_sign - envp[i]);
			new_node->value = ft_strdup(equal_sign + 1);
			new_node->next = NULL;
			if (!head)
				head = new_node;
			else
				tail->next = new_node;
			tail = new_node;
		}
		i++;
	}
	return (head);
	
}

int env_set(t_env **env , const char *name, const char *value)
{
	t_env *current = *env;
	t_env *node;

	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return (0); // success
		}
		current = current->next;
	}
	node = malloc(sizeof *(node));
	if (!node)
		return (1); // failure
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	node->next = *env;
	*env = node;
	return (0); // success
}
int env_unset(t_env **env, const char *name)
{
	t_env *current = *env;
	t_env *prev = NULL;

	while (current)
	{
		if (ft_strcmp(current->name, name) == 0) // todo
		{
			if (prev == NULL)
				*env = current->next; // head is being removed
			else
				prev->next = current->next;

			free(current->name);
			free(current->value);
			free(current);
			return (0); // success
		}
		prev = current;
		current = current->next;
	}
	return (1); // variable not found
}
char *ft_getenv(t_env *env_list, const char *name)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
void free_env(t_env *env_list)
{
	t_env *temp;

	while (env_list)
	{
		temp = env_list->next;
		free(env_list->name);
		free(env_list->value);
		free(env_list);
		env_list = temp;
	}
}