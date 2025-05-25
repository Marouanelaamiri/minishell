/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_question.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:52:04 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 00:53:29 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_question_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (i);
		i++;
	}
	return (-1);
}

char	*replace_question_heredoc(char *str, int index)
{
	char	*prefix;
	char	*suffix;
	char	*exit_code;
	char	*temp;

	exit_code = ft_itoa_gc(ft_update_exit_status(0, 0));
	prefix = ft_substr_gc(str, 0, index);
	suffix = ft_substr_gc(str, index + 2, ft_strlen(str) - (index + 2));
	temp = ft_strjoin_gc(prefix, exit_code);
	return (ft_strjoin_gc(temp, suffix));
}
