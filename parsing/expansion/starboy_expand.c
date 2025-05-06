/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starboy_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:42:56 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/03 19:52:31 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	convert_exit_code(t_token *t)
{
	char	*exit_code;
	char	*temp;
	char	*new_value;

	if (!t->value[2])
	{
		free(t->value);
		t->value = ft_itoa(ft_get_exit_status());
		return ;
	}
	else
	{
		exit_code = ft_itoa(ft_get_exit_status());
		temp = ft_strdup(t->value + 2);
		new_value = ft_strjoin(exit_code, temp);
		free(exit_code);
		free(temp);
		free(t->value);
		t->value = new_value;
	}
}

static void	number_before_dollar(t_token *t)
{
	free(t->value);
	t->value = ft_strdup("");
}

static void	expand_env_dollar(t_token *t, t_env *env)
{
	t_env	*env_list;
	char	*key_val;
	char	*val;
	if (!t->value)
		return ;
	env_list = env;
	key_val = ft_strdup(t->value + 1);
	val = NULL;
	
	while (env_list)
	{
		if (ft_strcmp(env_list->name, key_val) == 0)
		{
			val = ft_strdup(env_list->value);
			break ;
		}
		env_list = env_list->next;
	}
	free(t->value);
	if (val)
		t->value = val;
	else
		t->value = ft_strdup("");
	free(key_val);
}

void	starboy_expansion(t_token *t, t_env *env)
{
	t_token *hmstr;
	
	hmstr = t;
	while (hmstr)
	{
		if (hmstr->type == VAR && hmstr->value && hmstr->value[0] == '$')
		{
			if (hmstr->value[1] == '?')
				convert_exit_code(hmstr);
			else if (ft_isdigit(hmstr->value[1]))
				number_before_dollar(hmstr);
			else if (hmstr->value[1] != '\0')
				expand_env_dollar(hmstr, env);
		}
		// else if (hmstr->type == DQUOTE)
		// 	starboy_quote_expansion(hmstr, env);
		// implement the expansion double quotes
		hmstr = hmstr->next;
	}
}
