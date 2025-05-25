/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squotes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:57:27 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 18:58:16 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_single_quote(char c)
{
	return (c == '\'');
}

static int	count_chars_without_squotes(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!is_single_quote(str[i]))
			count++;
		i++;
	}
	return (count);
}

static void	copy_without_squotes(char *dst, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!is_single_quote(src[i]))
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
}

char	*remove_squotes(char *str)
{
	char	*new_str;
	int		size;

	if (!str)
		return (NULL);
	size = count_chars_without_squotes(str);
	if (size == 0)
		return (ft_strdup_gc(""));
	new_str = gc_malloc(size + 1, 63);
	if (!new_str)
		return (NULL);
	copy_without_squotes(new_str, str);
	return (new_str);
}
