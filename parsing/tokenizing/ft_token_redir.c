/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:24:50 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 01:25:43 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_type	get_redir_type(char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (APPEND);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (HEREDOC);
	else if (input[i] == '>')
		return (REDIR_OUT);
	return (REDIR_IN);
}

static char	*get_redir_value(t_type type)
{
	if (type == APPEND)
		return (ft_strdup_gc(">>"));
	if (type == HEREDOC)
		return (ft_strdup_gc("<<"));
	if (type == REDIR_OUT)
		return (ft_strdup_gc(">"));
	return (ft_strdup_gc("<"));
}

static int	get_redir_count(t_type type)
{
	if (type == APPEND || type == HEREDOC)
		return (2);
	return (1);
}

int	ft_handle_redir(t_data *data, char *input)
{
	t_type	type;
	char	*value;
	int		count;

	type = get_redir_type(input, data->i);
	value = get_redir_value(type);
	count = get_redir_count(type);
	if (!value)
	{
		data->error = 1;
		return (0);
	}
	lst_add_back_token(data, lst_new_token(type, value));
	return (count);
}
