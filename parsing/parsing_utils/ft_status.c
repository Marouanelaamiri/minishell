/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:34:43 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/15 20:26:37 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_update_exit_status(int status, int x)
{
	static int	exit_status;

	if (x == 63)
		exit_status = status;
	else if (x == 0)
		return (exit_status);
	return (0);
}
