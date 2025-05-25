/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starboy_quote_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:48:29 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 00:35:30 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	replace_all_dollars(t_token *t, t_env *env)
{
	int		index;
	char	*new_value;

	index = find_dollar(t->value);
	while (index != -1)
	{
		new_value = replace_dollar(t->value, index, env);
		t->value = new_value;
		index = find_dollar(t->value);
	}
}

static void	replace_all_questions(t_token *t)
{
	int		index;
	char	*new_value;

	index = find_question(t->value);
	while (index != -1)
	{
		new_value = replace_question(t->value, index);
		t->value = new_value;
		index = find_question(t->value);
	}
}

static void	replace_all_numbers(t_token *t)
{
	int		index;
	char	*new_value;

	index = find_number(t->value);
	while (index != -1)
	{
		new_value = replace_number(t->value, index);
		t->value = new_value;
		index = find_number(t->value);
	}
}

void	starboy_quote_expansion(t_token *t, t_env *env)
{
	if (!t || !t->value)
		return ;
	replace_all_dollars(t, env);
	replace_all_questions(t);
	replace_all_numbers(t);
	t->value = remove_dquotes(t->value, t->quoted);
	t->quoted = 1;
	t->type = WORD;
}
