/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_join_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:45:21 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/15 19:12:14 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	nodes_join_part2(t_token *tokens)
{
	t_token	*current;
	t_token	*tmp;
	char	*joined;

	current = tokens;
	while (current && current->next)
	{
		if (current->type == WORD && current->next->type == WORD)
		{
			joined = ft_strjoin_gc(current->value, current->next->value);
			if (!joined)
				return ;
			current->value = joined;
			tmp = current->next;
			current->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = current;
			continue ;
		}
		current = current->next;
	}
}
