/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_masking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:23:59 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 21:30:15 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mask_quoted_chars(char *str)
{
	int		h;
	char	quote;

	h = 0;
	while (str[h])
	{
		if (str[h] == '"' || str[h] == '\'')
		{
			quote = str[h];
			h++;
			if (str[h] == '\0')
				break ;
			while (str[h])
			{
				if (str[h] == quote)
					break ;
				str[h] *= -1;
				h++;
			}
		}
		if (str[h])
			h++;
	}
}

void	unmask_quoted_chars(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	while (token)
	{
		if (token->type == DQUOTE
			|| token->type == SQUOTE
			|| token->type == WORD)
		{
			if (token->value)
				mask_quoted_chars(token->value);
		}
		token = token->next;
	}
}
