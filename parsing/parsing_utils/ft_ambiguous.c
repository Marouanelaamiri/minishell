/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguous.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:09:24 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 19:00:44 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ambiguous_redirection(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		if (tokens->type == REDIR_IN
			|| tokens->type == REDIR_OUT
			|| tokens->type == APPEND)
		{
			next = tokens->next;
			while (next && next->type == SPCE)
				next = next->next;
			if (!next || next->type != WORD)
			{
				ft_putstr_fd("minishell: ambiguous redirection\n", 2);
				return (1);
			}
			if (next->next && next->next->type == WORD)
			{
				ft_putstr_fd("minishell: ambiguous redirection\n", 2);
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
