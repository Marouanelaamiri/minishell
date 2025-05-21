/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:24:43 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/15 16:39:09 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == HEREDOC || type == APPEND);
}

static int	ft_valid_pipe(t_token *t)
{
	// pipe at beginning or end
	if (!t->prev || !t->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}

	// skip space before and after
	t_token *prev = t->prev;
	while (prev && prev->type == SPCE)
		prev = prev->prev;

	t_token *next = t->next;
	while (next && next->type == SPCE)
		next = next->next;

	if (!prev || !next || prev->type == PIPE || ft_is_redir(prev->type) || next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (1);
}

static int	ft_valid_redir(t_token *t)
{
	t_token *next = t->next;
	while (next && next->type == SPCE)
		next = next->next;

	if (!next || next->type == PIPE || ft_is_redir(next->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (next && next->value)
			ft_putstr_fd(next->value, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

static int	ft_valid_word(char *value)
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

int	ft_syntax_check(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE && !ft_valid_pipe(curr))
			return (0);
		if (ft_is_redir(curr->type) && !ft_valid_redir(curr))
			return (0);
		if (curr->type == WORD && !ft_valid_word(curr->value))
			return (0);
		curr = curr->next;
	}
	return (1);
}


// static int ft_is_redir(t_type type)
// {
// 	return (type == REDIR_IN || type == REDIR_OUT || type == HEREDOC || type == APPEND);
// }

// static int ft_valid_pipe(t_token *t)
// {
// 	if (!t->next || !t->prev || ft_is_redir(t->prev->type) || (t->prev->prev != NULL && t->prev->prev->type == PIPE
// 		&& ft_is_redir(t->prev->prev->type))
// 		|| (t->prev->type == SPCE && !t->prev->prev)
// 		|| (t->next->type == SPCE && !t->next->next)
// 		|| (t->next->type == SPCE && t->next->next->type == PIPE) || t->next->type == PIPE)
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
// 		return (0);
// 	}
// 	return (1);
// }

// static int ft_valid_redir(t_token *t)
// {
// 	if (t->prev != NULL && t->prev->type == HEREDOC)
// 		return (1);
// 	if (!t->next || (t->next->type)
// 		|| (t->next->type == SPCE && !t->next->next)
// 		|| (t->next->type == SPCE && ft_is_redir(t->next->next->type))
// 		|| (t->next->type == SPCE && t->next->next != NULL && t->next->next->type == PIPE))
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
// 		ft_putstr_fd(t->value, 2);
// 		ft_putstr_fd("'\n", 2);
// 		return (0);
// 	}
// 	return (1);
// }

// static int ft_valid_word(char *value)
// {
// 	while (*value)
// 	{
// 		if (*value == '&' || *value == '(' || *value == ')')
// 		{
// 			ft_putstr_fd("minishell: syntax error: forbidden character `", 2);
// 			ft_putchar_fd(*value, 2);
// 			ft_putstr_fd("'\n", 2);
// 			return (0);
// 		}
// 		value++;
// 	}
// 	return (1);
// }

// int ft_syntax_check(t_token *tokens)
// {
// 	t_token	*current;

// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == PIPE && !ft_valid_pipe(current))
// 			return (0);
// 		if (ft_is_redir(current->type) && !ft_valid_redir(current))
// 			return (0);
// 		if (current->type == WORD && !ft_valid_word(current->value))
// 			return (0);
// 		current = current->next;
// 	}
// 	return (1);
// }
