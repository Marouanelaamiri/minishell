/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:59:46 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/01 20:17:18 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_check_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				if (quote == '\'')
					ft_putstr_fd("minishell: syntax error near unexpected token `'\n", 2);
				else
					ft_putstr_fd("minishell: syntax error near unexpected token `\"\n", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
