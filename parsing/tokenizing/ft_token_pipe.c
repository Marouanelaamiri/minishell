/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:54:18 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/01 20:30:19 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_handle_pipe(t_data *data)
{
	char	*pipe;
	pipe = ft_strdup("|");
	if (!pipe)
	{
		data->error = 1;
		return (0);
	}
	lst_add_back_token(data, lst_new_token(PIPE, pipe));
	data->i++;
	return (0);
}
