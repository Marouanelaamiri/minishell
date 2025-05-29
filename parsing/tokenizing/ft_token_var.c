/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:33:12 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/26 01:27:19 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_extract_var(t_data *data, char *input, int start, int j)
{
	if (input[data->i] == '?')
	{
		data->i++;
		return (ft_strdup_gc("$?"));
	}
	if (ft_isdigit(input[data->i]))
	{
		data->i++;
		return (ft_substr_gc(input, start, 2));
	}
	if (input[data->i] == '\"')
	{
		data->token->quoted = 1;
		return (ft_strdup_gc(""));
	}
	while (ft_isalnum(input[data->i]))
		data->i++;
	if (data->i == j)
		return (ft_strdup_gc("$"));
	return (ft_substr_gc(input, start, data->i - start));
}

static int	ft_handle_single_dollar(t_data *data)
{
	char	*value;

	data->i++;
	value = ft_strdup_gc("$");
	if (!value)
		return (ft_error(data));
	lst_add_back_token(data, lst_new_token(VAR, value));
	data->last_token->quoted = 1;
	return (0);
}

static int	ft_expand_multi_dollar_var(t_data *data, char *input,
		int count, int start)
{
	char	*value;
	char	*suffix;
	char	*full;
	int		j;

	data->i = start;
	value = ft_substr_gc(input, data->i, count);
	if (!value)
		return (ft_error(data));
	data->i += count;
	j = data->i;
	if (input[data->i] == '?')
		data->i++;
	else
		while (ft_isalnum(input[data->i]) || input[data->i] == '_')
			data->i++;
	suffix = ft_substr_gc(input, j, data->i - j);
	if (!suffix)
		return (ft_error(data));
	full = ft_strjoin_gc(value, suffix);
	if (!full)
		return (ft_error(data));
	lst_add_back_token(data, lst_new_token(VAR, full));
	return (0);
}

static int	ft_handle_multi_dollar(t_data *data, char *input,
		int count, int start)
{
	int		k;
	char	*value;

	k = data->i + count;
	if (ft_isalnum(input[k]) || input[k] == '_' || input[k] == '?')
		return (ft_expand_multi_dollar_var(data, input, count, start));
	value = ft_substr_gc(input, data->i, count);
	if (!value)
		return (ft_error(data));
	data->i += count;
	lst_add_back_token(data, lst_new_token(VAR, value));
	return (0);
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
		return (ft_handle_multi_dollar(data, input, dollar_count, start));
	if (!input[data->i + 1] || input[data->i + 1] == ' '
		|| (!ft_isalnum(input[data->i + 1]) && input[data->i + 1] != '_'
			&& input[data->i + 1] != '?'))
		return (ft_handle_single_dollar(data));
	data->i++;
	j = data->i;
	value = ft_extract_var(data, input, start, j);
	if (!value)
		return (ft_error(data));
	lst_add_back_token(data, lst_new_token(VAR, value));
	return (0);
}
