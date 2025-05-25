/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starboy_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:42:56 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 16:35:41 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_in_heredoc(t_token *token)
{
	t_token	*prev;

	prev = token->prev;
	while (prev && prev->type == SPCE)
		prev = prev->prev;
	if (prev && prev->type == HEREDOC)
		return (1);
	return (0);
}

static void	expand_variable(t_token *token, t_env *env)
{
	if (token->value[1] == '?')
		convert_exit_code(token);
	else if (ft_isdigit(token->value[1]))
		number_before_dollar(token);
	else if (token->value[1] != '\0')
		expand_env_dollar(token, env);
}

void	starboy_expansion(t_token *token, t_env *env)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (curr->type == VAR && curr->value && curr->value[0] == '$')
		{
			if (is_in_heredoc(curr))
			{
				curr = curr->next;
				continue ;
			}
			expand_variable(curr, env);
		}
		else if (curr->type == DQUOTE)
			starboy_quote_expansion(curr, env);
		else if (curr->type == SQUOTE)
		{
			curr->type = WORD;
			curr->value = remove_squotes(curr->value);
		}
		curr = curr->next;
	}
}
