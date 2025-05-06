/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:24:50 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/30 16:32:43 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_handle_redir(t_data *data, char *input)
{
	int	count;
	char	*value;
	t_type type;

	if (input[data->i] == '>' && input[data->i + 1] == '>')
	{
		value = ft_strdup(">>");
		count = 2;
		type = APPEND;
	}
	else if (input[data->i] == '<' && input[data->i + 1] == '<')
	{
		value = ft_strdup("<<");
		count = 2;
		type = HEREDOC;
	}
	else if (input[data->i] == '>')
	{
		value = ft_strdup(">");
		count = 1;
		type = REDIR_OUT;
	}
	else
	{
		value = ft_strdup("<");
		count = 1;
		type = REDIR_IN;
	}
	if (!value)
	{
		data->error = 1;
		return (0);
	}
	lst_add_back_token(data, lst_new_token(type, value));
	return (count);
}
