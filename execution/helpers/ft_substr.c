/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:29:37 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/20 11:03:23 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_l;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	s_l = strlen(s);
	i = 0;
	if (start >= s_l)
		return (strdup(""));
	if (len > (s_l - start))
		len = s_l - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	strlcpy(sub, &s[start], len + 1);
	sub[len] = '\0';
	return (sub);
}