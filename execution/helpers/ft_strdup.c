/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:04:52 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/25 11:53:24 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	dst = malloc(ft_strlen(src) + 1);
	if (!src)
		return (NULL);
	if (dst == NULL)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
