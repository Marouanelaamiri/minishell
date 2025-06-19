/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:49:24 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/15 20:27:04 by sojammal         ###   ########.fr       */
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

static int	should_remove_token(t_token *curr)
{
	if (curr->value && curr->type == SPCE && !curr->next && !curr->prev)
		return (1);
	if (!(curr->value && curr->value[0] == '\0' && curr->type != SPCE))
		return (0);
	if (curr->prev && curr->prev->prev
		&& (curr->prev->prev->type == REDIR_OUT
			|| curr->prev->prev->type == REDIR_IN
			|| curr->prev->prev->type == APPEND
			|| curr->prev->prev->type == HEREDOC))
		return (0);
	if (curr->prev && curr->prev->type == SPCE
		&& curr->prev->prev
		&& curr->prev->prev->type != HEREDOC
		&& curr->prev->prev->type != WORD)
		return (1);
	if (curr->prev && curr->prev->type == SPCE
		&& curr->prev->prev && curr->prev->prev->type == WORD
		&& curr->hidden == 1)
		return (1);
	if (curr->hidden == 1)
		return (1);
	return (0);
}

static int	has_valid_word_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->value && tmp->value[0] != '\0')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*tmp;
	int		any_word;

	if (!tokens || !*tokens)
		return ;
	any_word = has_valid_word_token(*tokens);
	curr = *tokens;
	while (curr)
	{
		tmp = curr->next;
		if (should_remove_token(curr))
			remove_token(tokens, curr);
		else if (!any_word && curr->type == SPCE)
			remove_token(tokens, curr);
		curr = tmp;
	}
}
