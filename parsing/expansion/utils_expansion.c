/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:43:13 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/25 21:24:11 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup_spec(const char *src, int *q)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!src)
		return ("\0");
	dst = gc_malloc(ft_strlen(src) + 1, 63);
	if (!dst)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '=')
		{
			*q = 1;
			break ;
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_full(const char *src, int q)
{
	char	*dst;
	size_t	i;
	size_t	len;

	if (!src)
		return ("\0");
	len = ft_strlen(src);
	if (q == 1)
		len++;
	dst = gc_malloc(len + 1, 63);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (q == 1)
		dst[i++] = '=';
	dst[i] = '\0';
	return (dst);
}
