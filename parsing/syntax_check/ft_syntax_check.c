/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:37:24 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/20 21:24:21 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_syntax_check(t_token *tokens)
{
	t_token *current = tokens;

	if (current && current->type == PIPE)
	{
		printf("Syntax error: unexpected pipe at the start\n");
		return (0);
	}

	while (current)
	{
		t_token *next = current->next;

		// Pipe checks
		if (current->type == PIPE)
		{
			if (!next)
			{
				printf("Syntax error: unexpected pipe at the end\n");
				return (0);
			}
			if (next->type == PIPE)
			{
				printf("Syntax error: unexpected pipe\n");
				return (0);
			}
			// ✅ Only WORD is valid right after a pipe (not a redirection alone)
			if (next->type != WORD)
			{
				printf("Syntax error: pipe not followed by a command\n");
				return (0);
			}
		}
		// Redirection checks
		if (current->type == REDIR_IN || current->type == REDIR_OUT ||
			current->type == APPEND || current->type == HEREDOC)
		{
			if (!next || next->type != WORD)
			{
				printf("Syntax error: redirection operator not followed by a word\n");
				return (0);
			}
		}

		current = current->next;
	}

	return (1);
}

int ft_check_quotes(const char *input)
{
	int i = 0;
	char quote = 0;

	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (quote == 0)
				quote = input[i]; // start quote
			else if (input[i] == quote)
				quote = 0; // close quote
		}
		i++;
	}
	if (quote)
	{
		if (quote == '\'')
			printf("Syntax error: unclosed single quote\n");
		else if (quote == '\"')
			printf("Syntax error: unclosed double quote\n");
		return (0);
	}
	return (1);
}
