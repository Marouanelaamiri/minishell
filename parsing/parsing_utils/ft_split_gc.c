/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:36:39 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 17:08:43 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_count_w(const char *s, char c)
{
	size_t	count;
	size_t	is_w;
	size_t	i;

	count = 0;
	is_w = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			is_w = 1;
		else if (is_w == 1)
		{
			count++;
			is_w = 0;
		}
		i++;
	}
	return (count);
}

static char	**ft_stor_list(char **list, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		if (j < i)
		{
			list[x] = ft_substr_gc(s, j, i - j);
			if (list[x] == NULL)
				return (NULL);
			x++;
		}
	}
	list[x] = NULL;
	return (list);
}

char	**ft_split_gc(char const *s, char c)
{
	char	**list;
	size_t	new_word;

	if (s == NULL)
		return (NULL);
	new_word = ft_count_w(s, c);
	list = gc_malloc((new_word + 1) * sizeof(char *), 63);
	if (list == NULL)
		return (NULL);
	list = ft_stor_list(list, s, c);
	return (list);
}
