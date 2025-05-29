/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starboy_expand_p2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:48:39 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 18:48:58 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_env_value(char *key, int has_equal, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
			return (ft_strdup_full(env->value, has_equal));
		env = env->next;
	}
	return (NULL);
}

static void	set_token_value(t_token *token, char *val)
{
	if (val)
	{
		token->value = val;
		token->hidden = 0;
	}
	else
	{
		token->value = ft_strdup_gc("");
		token->hidden = 1;
	}
}

void	expand_env_dollar(t_token *token, t_env *env)
{
	char	*key_val;
	char	*val;
	int		has_equal;

	if (!token->value)
		return ;
	has_equal = 0;
	key_val = ft_strdup_spec(token->value + 1, &has_equal);
	val = get_env_value(key_val, has_equal, env);
	set_token_value(token, val);
}

void	convert_exit_code(t_token *token)
{
	char	*exit_code;
	char	*temp;
	char	*new_value;

	if (!token->value[2])
	{
		token->value = ft_itoa_gc(ft_update_exit_status(0, 0));
		return ;
	}
	exit_code = ft_itoa_gc(ft_update_exit_status(0, 0));
	temp = ft_strdup_gc(token->value + 2);
	new_value = ft_strjoin_gc(exit_code, temp);
	token->value = new_value;
}

void	number_before_dollar(t_token *token)
{
	token->value = ft_strdup_gc("");
}
