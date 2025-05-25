/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:24:43 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 18:31:42 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_pipe(t_token *pipe_token)
{
	t_token	*prev;
	t_token	*next;

	if (!pipe_token->prev || !pipe_token->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	prev = pipe_token->prev;
	while (prev && prev->type == SPCE)
		prev = prev->prev;
	next = pipe_token->next;
	while (next && next->type == SPCE)
		next = next->next;
	if (!prev || !next || prev->type == PIPE
		|| is_redirection(prev->type) || next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (1);
}

static void	print_redir_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token && token->value)
		ft_putstr_fd(token->value, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

static int	is_valid_redirection(t_token *redir_token)
{
	t_token	*next;

	next = redir_token->next;
	while (next && next->type == SPCE)
		next = next->next;
	if (!next || next->type == PIPE || is_redirection(next->type))
	{
		print_redir_error(next);
		return (0);
	}
	return (1);
}

static int	is_valid_word(char *value)
{
	if (!value)
		return (1);
	while (*value)
	{
		if (*value == '&' || *value == '(' || *value == ')')
		{
			ft_putstr_fd("minishell: syntax error: forbidden character `", 2);
			ft_putchar_fd(*value, 2);
			ft_putstr_fd("'\n", 2);
			return (0);
		}
		value++;
	}
	return (1);
}

int	syntax_check(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE && !is_valid_pipe(curr))
			return (0);
		if (is_redirection(curr->type) && !is_valid_redirection(curr))
			return (0);
		if (curr->type == WORD && !is_valid_word(curr->value))
			return (0);
		curr = curr->next;
	}
	return (1);
}
