/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:53:17 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/25 23:56:42 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_init_data(t_data *data)
{
	data->token = NULL;
	data->last_token = NULL;
	data->i = 0;
	data->error = 0;
}

t_token	*ft_tokeniz(char *input)
{
	t_data	data;

	ft_init_data(&data);
	if (!input)
		return (NULL);
	while (input[data.i])
	{
		if (input[data.i] == ' ' || input[data.i] == '\t')
			data.i += ft_handle_space(&data, input);
		if (input[data.i] == '|')
			data.i += ft_handle_pipe(&data);
		else if (input[data.i] == '>' || input[data.i] == '<')
			data.i += ft_handle_redir(&data, input);
		else if (input[data.i] == '$')
			data.i += ft_handle_var(&data, input);
		else if (input[data.i] == '\'' || input[data.i] == '\"')
			data.i += ft_handle_quotes(&data, input);
		else
			data.i += ft_handle_word(&data, input);
	}
	if (data.error)
		return (NULL);
	return (data.token);
}
