/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isllnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:37:15 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/22 10:31:38 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static int	is_valid_digit(const char *str, int *length)
{
	int	count;

	count = 0;
	while (ft_isdigit(str[count]))
		count++;
	*length = count;
	if (count == 0)
		return (0);
	return (1);
}

static int	is_within_llimit(const char *start, int len, int sign)
{
	unsigned long long	value;
	unsigned long long	limit;
	int					i;
	int					digit;

	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MIN;
	value = 0;
	i = 0;
	while (i < len)
	{
		digit = start[i] - '0';
		if (value > limit / 10)
			return (0);
		if (value == limit / 10
			&& (unsigned long long)digit > limit % 10)
			return (0);
		value = value * 10 + digit;
		i++;
	}
	return (1);
}

int	ft_isllnum(const char *str)
{
	const char	*p;
	int			sign;
	const char	*digits_start;
	int			digit_count;

	if (str == NULL)
		return (0);
	p = str;
	while (ft_isspace(*p))
		p++;
	sign = get_sign(&p);
	digits_start = p;
	if (!is_valid_digit(p, &digit_count))
		return (0);
	p += digit_count;
	if (!is_within_llimit(digits_start, digit_count, sign))
		return (0);
	if (*p != '\0')
		return (0);
	return (1);
}
