/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:41:17 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 14:15:07 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export_list(t_env *env)
{
	t_env	**arr;

	arr = build_env_array(env);
	if (!arr)
		return (1);
	sort_env_array(arr);
	print_env_array(arr);
	free(arr);
	return (0);
}

t_env	**build_env_array(t_env *env)
{
	size_t	count;
	t_env	*current;
	t_env	**arr;

	current = env;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = malloc(sizeof (*arr) * (count + 1));
	if (!arr)
		return (NULL);
	current = env;
	count = 0;
	while (current)
	{
		arr[count++] = current;
		current = current->next;
	}
	arr[count] = NULL;
	return (arr);
}

void	sort_env_array(t_env **arr)
{
	size_t	i;
	size_t	j;
	t_env	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i]->name, arr[j]->name) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_array(t_env **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i]->name, "_") == 0)
		{
			i++;
			continue ;
		}
		if (arr[i]->value)
			printf("declare -x %s=\"%s\"\n", arr[i]->name, arr[i]->value);
		else
			printf("declare -x %s\n", arr[i]->name);
		i++;
	}
}
