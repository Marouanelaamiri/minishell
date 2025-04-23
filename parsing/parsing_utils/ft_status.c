/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:34:43 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/23 17:35:03 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_update_exit_status(int status)
{
	g_exit_status = status;
}

int ft_get_exit_status(void)
{
	return (g_exit_status);
}