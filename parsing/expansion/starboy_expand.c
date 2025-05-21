/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starboy_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:42:56 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/17 23:52:55 by sojammal         ###   ########.fr       */
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
		t->value = ft_itoa(ft_update_exit_status(0, 0));
		return ;
	}
	else
	{
		exit_code = ft_itoa(ft_update_exit_status(0, 0));
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
			t_token *prev = hmstr->prev;
			while (prev && prev->type == SPCE)
				prev = prev->prev;
		
			if (prev && prev->type == HEREDOC)
			{
				hmstr = hmstr->next;
				continue;
			}
			if (hmstr->value[1] == '?')
				convert_exit_code(hmstr);
			else if (ft_isdigit(hmstr->value[1]))
				number_before_dollar(hmstr);
			else if (hmstr->value[1] != '\0')
				expand_env_dollar(hmstr, env);
		}
		else if (hmstr->type == DQUOTE)
			starboy_quote_expansion(hmstr, env);
		else if (hmstr->type == SQUOTE)
		{
			hmstr->type = WORD;
			hmstr->value = remove_squotes(hmstr->value);
		}
		hmstr = hmstr->next;
	}
}
