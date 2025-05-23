/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:12:02 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 15:17:59 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_tokens(t_token *token)
{
	size_t	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

size_t	count_env_vars(t_env *env)
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

static void	free_av_partial(char **av, size_t i)
{
	while (i > 0)
		free(av[--i]);
	free(av);
}

static char	**fill_av_array(t_token *token, size_t count)
{
	char	**av;
	size_t	i;

	av = malloc(sizeof(char *) * (count + 1));
	if (!av)
		return (NULL);
	i = 0;
	while (token)
	{
		av[i] = ft_strdup(token->value);
		if (!av[i])
		{
			free_av_partial(av, i);
			return (NULL);
		}
		i++;
		token = token->next;
	}
	av[i] = NULL;
	return (av);
}

char	**token_to_av(t_token *token)
{
	size_t	count;

	if (!token)
		return (NULL);
	count = count_tokens(token);
	return (fill_av_array(token, count));
}
