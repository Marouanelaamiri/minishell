/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:10:40 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/21 11:30:03 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_env_vars(t_env *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		if (env->value != NULL)
			count++;
		env = env->next;
	}
	return (count);
}

static void	free_envp_partial(char **envp, size_t i)
{
	while (i-- > 0)
		free(envp[i]);
	free(envp);
}

static char	*build_env_entry(t_env *env_var)
{
	size_t	len;
	char	*entry;

	len = ft_strlen(env_var->name) + ft_strlen(env_var->value) + 2;
	entry = malloc(len);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, env_var->name, len);
	ft_strlcat(entry, "=", len);
	ft_strlcat(entry, env_var->value, len);
	return (entry);
}

char	**env_list_to_envp(t_env *env)
{
	char	**envp;
	size_t	count;
	size_t	i;

	count = count_env_vars(env);
	envp = malloc((count + 1) * (sizeof (*envp)));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = build_env_entry(env);
			if (!envp[i])
				return (free_envp_partial(envp, i), NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
