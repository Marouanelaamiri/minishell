/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:46:06 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/26 00:38:57 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_handle_redir_t(t_token **tokens, t_cmd *current)
{
	t_type	redir_type;
	char	*file;

	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || !(*tokens)->value)
		return (0);
	if ((*tokens)->type == SPCE)
		*tokens = (*tokens)->next;
	if (!*tokens || !(*tokens)->value)
		return (0);
	file = ft_strdup_gc((*tokens)->value);
	if (!file)
		return (0);
	ft_add_redir_to_cmd(current, redir_type, file, (*tokens)->quoted);
	*tokens = (*tokens)->next;
	return (1);
}

int	ft_handle_word_t(t_token *tokens, t_cmd *current)
{
	t_token	*arg;

	if (!tokens->value)
		return (1);
	arg = gc_malloc(sizeof(t_token), 63);
	if (!arg)
		return (0);
	arg->type = tokens->type;
	arg->value = ft_strdup_gc(tokens->value);
	arg->next = NULL;
	arg->prev = NULL;
	ft_add_arg_to_cmd(current, arg);
	return (1);
}

void	init_struct(t_cmd **head, t_cmd **last, t_cmd **current)
{
	*head = NULL;
	*last = NULL;
	*current = NULL;
}

static t_cmd	*ft_pipe_check(t_token **tokens, t_cmd *current, t_cmd **last)
{
	if (!current)
		return (NULL);
	*last = current;
	*tokens = (*tokens)->next;
	return (NULL);
}

t_cmd	*ft_parse_commands(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*current;

	init_struct(&head, &last, &current);
	while (tokens)
	{
		if (!current && !ft_prepare_cmd(&current, &head, &last))
			return (NULL);
		if (tokens->type == PIPE)
		{
			current = ft_pipe_check(&tokens, current, &last);
			continue ;
		}
		if (is_redirection(tokens->type))
		{
			if (!ft_handle_redir_t(&tokens, current))
				return (NULL);
			continue ;
		}
		if (tokens->type == WORD && !ft_handle_word_t(tokens, current))
			return (NULL);
		tokens = tokens->next;
	}
	return (head);
}
