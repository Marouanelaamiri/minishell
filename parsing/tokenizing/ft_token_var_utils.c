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

int	ft_error(t_data *data)
{
	data->error = 1;
	return (0);
}

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
