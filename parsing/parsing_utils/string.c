/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:08:32 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/05 01:12:24 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirection(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND);
}

char	*ft_substr_gc(const char *s, unsigned int start, size_t len)
{
	size_t	s_l;
	char	*sub;

	if (!s)
		return (NULL);
	s_l = ft_strlen(s);
	if (start >= s_l)
		return (ft_strdup_gc(""));
	if (len > (s_l - start))
		len = s_l - start;
	sub = gc_malloc(len + 1, 63);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, &s[start], len + 1);
	sub[len] = '\0';
	return (sub);
}

char	*ft_strdup_gc(const char *src)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!src)
		return ("\0");
	dst = gc_malloc(ft_strlen(src) + 1, 63);
	if (!src)
		return (NULL);
	if (!dst)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_gc(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_gc(s2));
	if (!s2)
		return (ft_strdup_gc(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	str = gc_malloc(sizeof(char) * (len + 1), 63);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin_gc(s1, s2);
	result = ft_strjoin_gc(temp, s3);
	return (result);
}
