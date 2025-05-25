/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:33:12 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 21:30:21 by sojammal         ###   ########.fr       */
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

	// 🔧 Check for multiple '$', and look ahead for valid varname
	if (dollar_count > 1)
	{
		int k = data->i + dollar_count; // point to char after $$$...

		if (ft_isalnum(input[k]) || input[k] == '_' || input[k] == '?')
		{
			// 🧠 Compose token like "$$USER" or "$$$?"
			data->i = start;
			value = ft_substr_gc(input, data->i, dollar_count); // Get $$$
			if (!value)
			{
				data->error = 1;
				return (0);
			}
			data->i += dollar_count;

			// Now parse the variable name after the dollars
			j = data->i;
			if (input[data->i] == '?')
				data->i++;
			else
			{
				while (ft_isalnum(input[data->i]) || input[data->i] == '_')
					data->i++;
			}
			char *suffix = ft_substr_gc(input, j, data->i - j); // Get USER or ?
			if (!suffix)
			{
				data->error = 1;
				return (0);
			}
			char *full = ft_strjoin_gc(value, suffix);
			if (!full)
			{
				data->error = 1;
				return (0);
			}
			lst_add_back_token(data, lst_new_token(VAR, full));
			return (0);
		}
		else
		{
			// Keep your existing logic for just "$$$$"
			value = ft_substr_gc(input, data->i, dollar_count);
			data->i += dollar_count;
			if (!value)
			{
				data->error = 1;
				return (0);
			}
			lst_add_back_token(data, lst_new_token(VAR, value)); // VAR token with literal "$$$$"
			return (0);
		}
	}

	if (!input[data->i + 1] || input[data->i + 1] == ' ' || (!ft_isalnum(input[data->i + 1]) && input[data->i + 1] != '_' && input[data->i + 1] != '?'))
	{
		data->i++;
		value = ft_strdup_gc("$");
		if (!value)
		{
			data->error = 1;
			return (0);
		}
		lst_add_back_token(data, lst_new_token(VAR, value));
		data->last_token->quoted = 1;
		return (0);
	}

	data->i++;
	j = data->i;

	if (input[data->i] == '?')
	{
		data->i++;
		value = ft_strdup_gc("$?");
	}
	else if (ft_isdigit(input[data->i]))
	{
		data->i++;
		value = ft_substr_gc(input, start, 2);
	}
	else if (input[data->i] == '\"') // handle $""
	{
		value = ft_strdup_gc("");
		data->token->quoted = 1;
	}
	else
	{
		while (ft_isalnum(input[data->i]) || input[data->i] == '_' ||
			(input[data->i] && input[data->i + 1] && input[data->i + 1] == '$') ||
			(input[data->i] && input[data->i - 1] && input[data->i - 1] == '$'))
			data->i++;
		if (data->i == j)
			value = ft_strdup_gc("$");
		else
			value = ft_substr_gc(input, start, data->i - start);
	}

	if (!value)
	{
		data->error = 1;
		return (0);
	}
	lst_add_back_token(data, lst_new_token(VAR, value));
	return (0);
}

// static int	handle_multiple_dollars(t_data *data, char *input, int dollar_count)
// {
// 	char	*value;

// 	value = ft_substr_gc(input, data->i, dollar_count);
// 	data->i += dollar_count;
// 	if (!value)
// 	{
// 		data->error = 1;
// 		return (0);
// 	}
// 	lst_add_back_token(data, lst_new_token(VAR, value));
// 	return (1);
// }

// static int	handle_single_dollar(t_data *data)
// {
// 	char	*value;

// 	data->i++;
// 	value = ft_strdup_gc("$");
// 	if (!value)
// 	{
// 		data->error = 1;
// 		return (0);
// 	}
// 	lst_add_back_token(data, lst_new_token(VAR, value));
// 	return (1);
// }

// static char	*extract_var_value(t_data *data, char *input, int start)
// {
// 	int	j;

// 	j = ++data->i;
// 	if (input[data->i] == '?')
// 	{
// 		data->i++;
// 		return (ft_strdup_gc("$?"));
// 	}
// 	else if (ft_isdigit(input[data->i]))
// 	{
// 		data->i++;
// 		return (ft_substr_gc(input, start, 2));
// 	}
// 	else if (input[data->i] == '\"')
// 		return (ft_strdup_gc(""));
// 	while (ft_isalnum(input[data->i]) || input[data->i] == '_'
// 		|| (input[data->i] && input[data->i + 1] == '$')
// 		|| (input[data->i] && data->i > 0 && input[data->i - 1] == '$'))
// 		data->i++;
// 	if (data->i == j)
// 		return (ft_strdup_gc("$"));
// 	return (ft_substr(input, start, data->i - start));
// }

// int	ft_handle_var(t_data *data, char *input)
// {
// 	int		start;
// 	int		dollar_count;
// 	char	*value;

// 	start = data->i;
// 	dollar_count = ft_count_dollars(input, data->i);
// 	if (dollar_count > 1)
// 		return (handle_multiple_dollars(data, input, dollar_count));
// 	if (!input[data->i + 1] || input[data->i + 1] == ' '
// 		|| (!ft_isalnum(input[data->i + 1]) && input[data->i + 1] != '_'
// 			&& input[data->i + 1] != '?'))
// 		return (handle_single_dollar(data));
// 	value = extract_var_value(data, input, start);
// 	if (!value)
// 	{
// 		data->error = 1;
// 		return (0);
// 	}
// 	lst_add_back_token(data, lst_new_token(VAR, value));
// 	return (0);
// }
