/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:37:15 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/21 15:58:11 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnum(const char *str)
{
	const char			*ptr;
	int					sign;
	int					digit;
	unsigned long long	num;

	ptr = str;
	sign = 1;
	num = 0;
	while (*ptr == ' ' || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	if (!*ptr)
		return (0);
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
			return (0);
		digit = *ptr - '0';
		if (sign == 1
			&& (num > LLONG_MAX / 10
				|| (num == LLONG_MAX / 10
					&& (unsigned long long)digit > LLONG_MAX % 10)))
			return (0);
		if (sign == -1
			&& (num > -(LLONG_MIN / 10)
				|| (num == -(LLONG_MIN / 10)
					&& (unsigned long long)digit > -(LLONG_MIN % 10))))
			return (0);
		num = num * 10 + digit;
		ptr++;
	}
	return (1);
}
