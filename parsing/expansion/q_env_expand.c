/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_env_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:54:27 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 00:29:01 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_variable(char *str, int index)
{
	int	h;
	int	len;

	h = index + 1;
	len = 0;
	while (str[h + len] && ft_isalnum(str[h + len]))
		len++;
	return (ft_substr_gc(str, h, len));
}

char	*get_value(t_env *env, char *key_val)
{
	while (env)
	{
		if (ft_strcmp(env->name, key_val) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*replace_dollar(char *str, int index, t_env *env)
{
	char	*key_val;
	char	*val;
	char	*new_str;

	key_val = get_variable(str, index);
	if (!key_val)
		return (NULL);
	val = get_value(env, key_val);
	if (!val)
		val = ft_strdup_gc("");
	else
		val = ft_strdup_gc(val);
	if (!val)
		return (NULL);
	new_str = ft_strjoin_gc(ft_substr_gc(str, 0, index), val);
	if (!new_str)
		return (NULL);
	return (ft_strjoin_gc(new_str, ft_strdup_gc(&str[index
					+ ft_strlen(key_val) + 1])));
}
