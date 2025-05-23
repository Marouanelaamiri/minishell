/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:59:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 14:14:55 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd *cmd, t_env **env)
{
	char	*resolved;
	t_env	*current;

	(void)cmd;
	resolved = find_executable("env", *env);
	if (resolved)
	{
		env_set(env, "_", resolved);
		free (resolved);
	}
	current = *env;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
