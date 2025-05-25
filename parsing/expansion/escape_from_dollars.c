/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_from_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:30:17 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 21:19:53 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*join_gc(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin_gc(s1, s2);
	return (joined);
}

static int	handle_dollar_sequence(char *value, int i, char **result)
{
	int	dcount;

	dcount = 0;
	while (value[i + dcount] == '$')
		dcount++;
	if (dcount % 2 != 0)
		*result = join_gc(*result, "$");
	return (dcount);
}

static void	transform_dollar_value(t_token *token)
{
	int		h;
	char	*result;
	char	buf[2];

	h = 0;
	result = ft_strdup_gc("");
	while (token->value[h])
	{
		if (token->value[h] == '$')
			h += handle_dollar_sequence(token->value, h, &result);
		else
		{
			buf[0] = token->value[h];
			buf[1] = '\0';
			result = join_gc(result, buf);
			h++;
		}
	}
	token->value = result;
}

static void	process_dollar_token(t_token *token, int in_squote)
{
	if (!token || !token->value || in_squote)
		return ;
	if (token->value[0] == '$' && token->value[1] == '\0')
		return ;
	transform_dollar_value(token);
}

void	escape_from_dollars(t_token *token_list)
{
	t_token	*cur;
	int		in_squote;

	cur = token_list;
	while (cur)
	{
		in_squote = (cur->type == SQUOTE);
		if (cur->type == WORD || (ft_strchr(cur->value, '$') && !in_squote))
			process_dollar_token(cur, in_squote);
		cur = cur->next;
	}
}
