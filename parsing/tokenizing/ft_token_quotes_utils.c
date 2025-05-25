/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:20:22 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 01:20:32 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_type	get_quote_type(char quote)
{
	if (quote == '\'')
		return (SQUOTE);
	return (DQUOTE);
}

int	is_quote_closed(char *input, int i, char quote)
{
	while (input[i])
	{
		if (input[i] == quote)
			return (1);
		i++;
	}
	return (0);
}
