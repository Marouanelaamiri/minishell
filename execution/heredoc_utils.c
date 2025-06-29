/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:03:37 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/20 01:18:39 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 1;
		close(0);
	}
}

int	is_heredoc_delim(t_token *token)
{
	size_t	len;

	if (!token || !token->value)
		return (0);
	len = ft_strlen(token->value);
	if ((len == 1 && token->value[0] == '$') || len == 0)
	{
		if (token->next && (token->next->type == DQUOTE
				|| token->next->type == SQUOTE))
			return (1);
	}
	return (0);
}
