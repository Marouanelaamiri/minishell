/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:52:27 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/25 23:56:29 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_process_quote(t_data *data, char *input, char quote)
{
	int		start;
	t_type	type;
	char	*value;
	t_token	*token;

	start = data->i;
	data->i++;
	while (input[data->i] && input[data->i] != quote)
	{
		if (quote == '\"' && input[data->i] == '$')
			ft_handle_var(data, input);
		else
			data->i++;
	}
	if (input[data->i] != quote)
		return (data->error = 1, 0);
	if (quote == '\'')
		type = SQUOTE;
	else
		type = DQUOTE;
	value = ft_substr_gc(input, start, data->i - start + 1);
	token = lst_new_token(type, value);
	token->quoted = 1;
	lst_add_back_token(data, token);
	return (1);
}

int	ft_handle_quotes(t_data *data, char *input)
{
	char	quote;

	quote = input[data->i];
	if (!ft_process_quote(data, input, quote))
		return (0);
	data->i++;
	return (0);
}
