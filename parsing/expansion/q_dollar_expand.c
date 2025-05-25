/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_dollar_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:53:58 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 21:05:29 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_question(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (i);
		i++;
	}
	return (-1);
}

int	find_number(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			return (i);
		i++;
	}
	return (-1);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && ft_isalnum(str[i + 1]))
			return (i);
		i++;
	}
	return (-1);
}

char	*replace_question(char *str, int index)
{
	char	*exit_code;
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*new_str;

	exit_code = ft_itoa_gc(ft_update_exit_status(0, 0));
	if (!exit_code)
		return (NULL);
	prefix = ft_substr_gc(str, 0, index);
	if (!prefix)
		return (NULL);
	suffix = ft_substr_gc(str, index + 2, ft_strlen(str) - (index + 2));
	if (!suffix)
		return (NULL);
	temp = ft_strjoin_gc(prefix, exit_code);
	if (!temp)
		return (NULL);
	new_str = ft_strjoin_gc(temp, suffix);
	return (new_str);
}

char	*replace_number(char *str, int index)
{
	char	*prefix;
	char	*suffix;
	char	*new_str;

	prefix = ft_substr_gc(str, 0, index);
	if (!prefix)
		return (NULL);
	suffix = ft_substr_gc(str, index + 2, ft_strlen(str) - (index + 2));
	if (!suffix)
		return (NULL);
	new_str = ft_strjoin_gc(prefix, suffix);
	return (new_str);
}
