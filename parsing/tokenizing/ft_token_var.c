/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:33:12 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/15 18:12:23 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_count_dollars(const char *input, int i)
{
	int count = 0;

	while (input[i] == '$')
	{
		count++;
		i++;
	}
	return (count);
}

int	ft_handle_var(t_data *data, char *input)
{
	int		start;
	int		j;
	int		dollar_count;
	char	*value;

	start = data->i;
	dollar_count = ft_count_dollars(input, data->i);

	if (dollar_count > 1)
	{
		value = ft_substr(input, data->i, dollar_count);
		data->i += dollar_count;
		if (!value)
		{
			data->error = 1;
			return (0);
		}
		lst_add_back_token(data, lst_new_token(VAR, value)); // VAR token with literal "$$$$"
		return (0);
	}
	if (!input[data->i + 1] || input[data->i + 1] == ' ' || (!ft_isalnum(input[data->i + 1]) && input[data->i + 1] != '_' && input[data->i + 1] != '?'))
	{
		data->i++;
		value = ft_strdup("$");
		if (!value)
		{
			data->error = 1;
			return (0);
		}
		lst_add_back_token(data, lst_new_token(VAR, value));
		return (0);
	}

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
		value = ft_strdup("");
	}
	else
	{
		while (ft_isalnum(input[data->i]) || input[data->i] == '_' ||
			(input[data->i] && input[data->i + 1] && input[data->i + 1] == '$') ||
			(input[data->i] && input[data->i - 1] && input[data->i - 1] == '$'))
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
	return (0);
}
