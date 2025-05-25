/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_join_v1_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:19:21 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 16:41:44 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	not_redir(t_token *node)
{
	return (node->type != REDIR_IN
		&& node->type != REDIR_OUT
		&& node->type != HEREDOC
		&& node->type != APPEND);
}

void	handle_prev_next(t_token *current, t_token *prev, t_token *next)
{
	char	*joined;

	joined = ft_strjoin3(prev->value, current->value, next->value);
	current->value = joined;
	if (prev->prev)
		prev->prev->next = current;
	current->prev = prev->prev;
	if (next->next)
		next->next->prev = current;
	current->next = next->next;
	current->type = WORD;
}

void	handle_prev(t_token *current, t_token *prev)
{
	char	*joined;

	joined = ft_strjoin_gc(prev->value, current->value);
	current->value = joined;
	if (prev->prev)
		prev->prev->next = current;
	current->prev = prev->prev;
	current->type = WORD;
}

void	handle_next(t_token *current, t_token *next)
{
	char	*joined;

	joined = ft_strjoin_gc(current->value, next->value);
	current->value = joined;
	if (next->next)
		next->next->prev = current;
	current->next = next->next;
	current->type = WORD;
}

void	handle_single(t_token *current)
{
	char	*joined;

	joined = ft_strdup_gc(current->value);
	current->value = joined;
	current->type = WORD;
}
