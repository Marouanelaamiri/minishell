/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:32:18 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/01 14:39:08 by malaamir         ###   ########.fr       */
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
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return (0);
		}
		current = current->next;
	}
	node = malloc(sizeof *(node));
	if (!node)
		return (1);
	node->name = ft_strdup(name);
	if(value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = *env;
	*env = node;
	return (0);
}
int env_unset(t_env **env, const char *name)
{
	t_env *current = *env;
	t_env *prev = NULL;

	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;

			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
char *ft_getenv(t_env *env_list, const char *name)
{
	if (!name || !*name)
		return (NULL);
	
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
void update_shell_level(t_env **env)
{
	char *lvl_str = ft_getenv(*env, "SHLVL");
	int lvl = 0;
	char *new_lvl = NULL;

	if (lvl_str)
		lvl = atoi(lvl_str);
	lvl++;
	if (lvl < 0)
		lvl = 0;
	else if (lvl > 999)
		lvl = 1;

	new_lvl = ft_itoa(lvl);
	if (new_lvl)
	{
		env_set(env, "SHLVL", new_lvl);
		free(new_lvl);
	}
}
