/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:51:34 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 20:51:49 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*remove_hidden_dollars(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*clean;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(str);
	clean = gc_malloc(len + 1, 63);
	if (!clean)
		return (NULL);
	while (str[i])
	{
		if ((unsigned char)str[i] != (unsigned char)('$' * -1))
		{
			clean[j] = str[i];
			j++;
		}
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

void	clean_hidden_dollars(t_token *tokens)
{
	t_token	*curr;
	char	*clean;

	curr = tokens;
	while (curr)
	{
		clean = remove_hidden_dollars(curr->value);
		curr->value = clean;
		curr = curr->next;
	}
}
