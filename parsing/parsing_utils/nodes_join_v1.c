/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_join_v1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:18:40 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 16:52:35 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_var_node(t_token *current)
{
	t_token	*prev;
	t_token	*next;

	prev = current->prev;
	next = current->next;
	if (prev && next && prev->type != SPCE && not_redir(prev)
		&& next->type != SPCE && not_redir(next))
		handle_prev_next(current, prev, next);
	else if (prev && prev->type != SPCE && not_redir(prev))
		handle_prev(current, prev);
	else if (next && next->type != SPCE && not_redir(next))
		handle_next(current, next);
	else
		handle_single(current);
}

void	nodes_join(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == VAR)
		{
			process_var_node(current);
			continue ;
		}
		current = current->next;
	}
}
