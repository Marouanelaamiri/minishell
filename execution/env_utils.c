/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:32:18 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/17 13:11:51 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_set(t_env **env, const char *name, const char *value)
{
	t_env	*node;

	if (update_existing_env(*env, name, value) == 0)
		return (0);
	node = malloc(sizeof *(node));
	if (!node)
		return (1);
	node->name = ft_strdup(name);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = *env;
	*env = node;
	return (0);
}

int	env_unset(t_env **env, const char *name)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
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

char	*ft_getenv(t_env *env_list, const char *name)
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

void	update_shell_level(t_env **env)
{
	char	*lvl_str;
	int		lvl;
	char	*new_lvl;

	lvl_str = ft_getenv(*env, "SHLVL");
	lvl = 0;
	new_lvl = NULL;
	if (lvl_str)
		lvl = ft_atoi(lvl_str);
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
