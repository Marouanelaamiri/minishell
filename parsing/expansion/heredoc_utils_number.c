/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:52:23 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 00:52:43 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_number_heredoc(char *str)
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

char	*replace_number_heredoc(char *str, int index)
{
	char	*prefix;
	char	*suffix;

	prefix = ft_substr_gc(str, 0, index);
	suffix = ft_substr_gc(str, index + 2, ft_strlen(str) - (index + 2));
	return (ft_strjoin_gc(prefix, suffix));
}
