/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:51:36 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 00:54:08 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_dollar_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && ft_isalnum(str[i + 1]))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_variable_heredoc(char *str, int index)
{
	int	start;
	int	len;

	start = index + 1;
	len = 0;
	while (str[start + len] && ft_isalnum(str[start + len]))
		len++;
	return (ft_substr_gc(str, start, len));
}

char	*get_value_heredoc(t_env *env, char *key_val)
{
	while (env)
	{
		if (ft_strcmp(env->name, key_val) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*replace_dollar_heredoc(char *str, int index, t_env *env)
{
	char	*prefix;
	char	*suffix;
	char	*key_val;
	char	*val;
	char	*temp;

	key_val = get_variable_heredoc(str, index);
	prefix = ft_substr_gc(str, 0, index);
	suffix = ft_strdup_gc(&str[index + ft_strlen(key_val) + 1]);
	val = get_value_heredoc(env, key_val);
	if (!val)
		val = ft_strdup_gc("");
	else
		val = ft_strdup_gc(val);
	temp = ft_strjoin_gc(prefix, val);
	return (ft_strjoin_gc(temp, suffix));
}
