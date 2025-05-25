/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:42:38 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 16:51:41 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lst_remove_token(t_token **head, t_token *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
}

void	lst_insert_before(t_token **head, t_token *node, t_token *new_token)
{
	if (!node || !new_token)
		return ;
	new_token->next = node;
	new_token->prev = node->prev;
	if (node->prev)
		node->prev->next = new_token;
	else
		*head = new_token;
	node->prev = new_token;
}

static int	is_assignment_word(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (str[i] == '=');
}

static t_token	*split_and_insert(t_token **tokens, t_token *current)
{
	char		**split;
	int			i;
	t_token		*new_token;
	t_token		*tmp;

	if (ft_strchr(current->value, ' '))
		split = ft_split_gc(current->value, ' ');
	else
		split = ft_split_gc(current->value, '\t');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		new_token = lst_new_token(WORD, ft_strdup_gc(split[i]));
		if (!new_token)
			return (NULL);
		lst_insert_before(tokens, current, new_token);
		i++;
	}
	tmp = current;
	current = current->next;
	lst_remove_token(tokens, tmp);
	return (current);
}

void	field_split_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == WORD
			&& current->value
			&& current->quoted == 0
			&& !is_assignment_word(current->value)
			&& (ft_strchr(current->value, ' ')
				|| ft_strchr(current->value, '\t')))
		{
			current = split_and_insert(tokens, current);
			continue ;
		}
		current = current->next;
	}
}
