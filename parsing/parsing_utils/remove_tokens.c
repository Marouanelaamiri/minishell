/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:49:24 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 20:49:50 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_token(t_token **head, t_token *to_remove)
{
	if (!head || !*head || !to_remove)
		return ;
	if (to_remove == *head)
		*head = to_remove->next;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*tmp;

	curr = *tokens;
	while (curr)
	{
		tmp = curr->next;
		if (curr->value && curr->value[0] == '\0'
			&& curr->type != SPCE)
		{
			if (curr->prev && curr->prev->type == SPCE
				&& curr->prev->prev
				&& curr->prev->prev->type != HEREDOC
				&& curr->prev->prev->type != WORD)
			{
				remove_token(tokens, curr);
			}
		}
		curr = tmp;
	}
}
