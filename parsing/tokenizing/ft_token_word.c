/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:40:50 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 17:15:18 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	like_that(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\''
		|| c == '\"' || c == '$' || c == 32 || (c >= 9 && c <= 13)
		|| c == '\n' || c == '\0')
		return (0);
	else
		return (1);
}

int	ft_handle_word(t_data *data, char *input)
{
	int		start;
	char	*value;

	start = data->i;
	while (input[data->i] && like_that(input[data->i]))
		data->i++;
	if (start == data->i)
		return (0);
	value = ft_substr_gc(input, start, data->i - start);
	if (!value)
	{
		data->error = 1;
		return (0);
	}
	lst_add_back_token(data, lst_new_token(WORD, value));
	return (0);
}
