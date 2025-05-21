/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:09:14 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/21 15:58:39 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	ch;
	char	*ret;

	ch = (char) c;
	i = 0;
	ret = NULL;
	while (s[i])
	{
		if (s[i] == ch)
			ret = (char *) &s[i];
		i++;
	}
	if (ch == '\0')
		return ((char *) &s[i]);
	else
		return (ret);
}
