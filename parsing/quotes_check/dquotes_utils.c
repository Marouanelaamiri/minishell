/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:51:11 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 18:51:25 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_quote(char c)
{
	return (c == '"');
}

static int	count_non_quotes(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!is_quote(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*remove_dquotes(char *str, int quoted)
{
	char	*new_str;
	int		i;
	int		j;
	int		size;

	(void)quoted;
	if (!str)
		return (NULL);
	size = count_non_quotes(str);
	new_str = gc_malloc(size + 1, 63);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_quote(str[i]))
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
