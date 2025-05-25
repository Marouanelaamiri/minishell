/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:34:43 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/25 12:18:57 by malaamir         ###   ########.fr       */
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
