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

void	expand_env_dollar(t_token *token, t_env *env)
{
	t_env	*env_list;
	char	*key_val;
	char	*val;
	int		has_equal;

	if (!token->value)
		return ;
	has_equal = 0;
	env_list = env;
	key_val = ft_strdup_spec(token->value + 1, &has_equal);
	val = NULL;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, key_val) == 0)
		{
			val = ft_strdup_full(env_list->value, has_equal);
			break ;
		}
		env_list = env_list->next;
	}
	if (val)
		token->value = val;
	else
		token->value = ft_strdup_gc("");
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
