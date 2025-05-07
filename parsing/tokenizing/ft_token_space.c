/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:00:07 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/30 18:12:40 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_handle_space(t_data *data, char *input)
{
	int count = 0;

	while (ft_isspace(input[data->i + count]))
		count++;
	return (count);
}
