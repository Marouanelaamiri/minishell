/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguous.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:09:24 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/16 22:40:24 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ambiguous_redirection(t_token *tokens)
{
	t_token	*hmstr;

	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT 
			|| tokens->type == APPEND)
		{
			hmstr = tokens->next;
			while (hmstr && hmstr->type == SPCE)
				hmstr = hmstr->next;
			if ((!hmstr->value || hmstr->value[0] == '\0') 
				|| ft_strchr(hmstr->value, ' ') || ft_strchr(hmstr->value, '\t'))
			{
				ft_putstr_fd("minishell: ambiguous redirection\n", 2);
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}