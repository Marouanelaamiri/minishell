/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_from_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:30:17 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/03 16:38:05 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	dollar_length(const char *str)
{
	int	count = 0;
	int i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
		
	}
	return (count);
}

// Hide ALL dollar signs (replace with ASCII 1 as garbage value)
static void	ft_hide_all(t_token *token, int count)
{
	int	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && count % 2 == 0)
			token->value[i] *= -1; // Replace with garbage value
		i++;
	}
}

// Keep only one dollar sign, shift rest of the string
static void	ft_single_dollar(t_token *token, int count)
{
	// (void)count; // Unused variable
	int	i = 1;
	int	j = 1;

	while (token->value[i + (count - 1)])
	{
		token->value[j] = token->value[i + (count - 1)];
		i++;
		j++;
	}
	token->value[j] = '\0';
	// free(token->value);
	// token->value = ft_strdup("$");
}

// Process a token depending on quote context
static void	process_dollar_token(t_token *token, int inside_d, int inside_s)
{
	(void)inside_d; // Unused variable
	int	dollar_len;

	if (!token || !token->value || inside_s)
		return;

	dollar_len = dollar_length(token->value);
	if (dollar_len == 0)
		return;

	if (dollar_len % 2 == 0)
		ft_hide_all(token, dollar_len);
	else if (dollar_len % 2 != 0)
		ft_single_dollar(token, dollar_len);
}

// Main loop that tracks quotes and applies dollar logic
void	escape_from_dollars(t_token *t)
{
	t_token	*cur = t;
	int	inside_d = 0;
	int	inside_s = 0;

	while (cur)
	{
		inside_d = 0;
		inside_s = 0;
		if (cur->type == SQUOTE)
			inside_s = 1;
		else if (cur->type == DQUOTE)
			inside_d = 1;
		
		if (cur->type == VAR || (ft_strchr(cur->value, '$') && !inside_s))
			process_dollar_token(cur, inside_d, inside_s);
		// if (inside_d)
		// 	process_dq_dolllar(cur);

		cur = cur->next;
	}
}

