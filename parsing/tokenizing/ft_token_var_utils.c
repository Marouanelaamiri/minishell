/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_var_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:31:28 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 20:05:22 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	add_var_token(t_data *data, char *value)
// {
// 	t_token	*token;

// 	if (!value)
// 		return (data->error = 1, 0);
// 	token = lst_new_token(VAR, value);
// 	if (!token)
// 		return (data->error = 1, 0);
// 	lst_add_back_token(data, token);
// 	return (1);
// }

int	ft_count_dollars(const char *input, int i)
{
	int	count;

	count = 0;
	while (input[i] == '$')
	{
		count++;
		i++;
	}
	return (count);
}
