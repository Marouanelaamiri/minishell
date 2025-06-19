/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:51:11 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/15 20:27:15 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_dquotes(char *str, int quoted)
{
	char	*new_str;
	int		len;

	(void)quoted;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
	{
		new_str = gc_malloc(len - 1, 63);
		if (!new_str)
			return (NULL);
		ft_strlcpy(new_str, str + 1, len - 1);
	}
	else
		new_str = ft_strdup_gc(str);
	return (new_str);
}
