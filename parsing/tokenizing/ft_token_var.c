/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:33:12 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/03 16:27:58 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_handle_var(t_data *data, char *input)
{
	int		start;
	int		j;
	char	*value;

	start = data->i;
	data->i++;
	j = data->i;

	if (input[data->i] == '?')
	{
		data->i++;
		value = ft_strdup("$?");
	}
	else if (ft_isdigit(input[data->i]))
	{
		data->i++;
		value = ft_substr(input, start, 2);
	}
	else if (input[data->i] == '\"') // handle $""
	{
		value = ft_strdup(""); // we store it as empty string
	}
	else
	{
		while (ft_isalnum(input[data->i]) || input[data->i] == '_' || (input[data->i] && input[data->i + 1] && input[data->i + 1] == '$') || (input[data->i] && input[data->i - 1] && input[data->i - 1] == '$'))
			data->i++;
		if (data->i == j)
			value = ft_strdup("$");
		else
			value = ft_substr(input, start, data->i - start);
	}

	if (!value)
	{
		data->error = 1;
		return (0);
	}
	lst_add_back_token(data, lst_new_token(VAR, value));
	// free(value);
	return (0);
}

