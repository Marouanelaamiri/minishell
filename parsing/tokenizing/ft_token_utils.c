/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:36:01 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 01:37:02 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*lst_new_token(t_type type, char *value)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), 63);
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->quoted = 0;
	token->hidden = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	lst_add_back_token(t_data *data, t_token *new)
{
	if (!new)
	{
		data->error = 1;
		return ;
	}
	if (!data->token)
	{
		data->token = new;
		data->last_token = new;
	}
	else
	{
		new->prev = data->last_token;
		data->last_token->next = new;
		data->last_token = new;
	}
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}
