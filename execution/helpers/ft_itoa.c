/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:00:19 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/21 10:21:55 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_count_nb(int nb)
{
	int	nb_l;

	nb_l = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb_l = 1;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		nb_l++;
	}
	return (nb_l);
}

static char	*ft_stor_list(char *list, int nb_l, int nb)
{
	int	i;

	i = nb_l;
	list[nb_l] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		nb_l--;
	}
	while (nb_l > 0)
	{
		list[i - 1] = (nb % 10) + '0';
		nb_l--;
		i--;
		nb /= 10;
	}
	return (list);
}

static char	*ft_locate_list(int nb_l, int nb)
{
	char	*list;

	if (nb >= 0)
	{
		list = (char *)malloc(nb_l + 1);
		if (!list)
			return (NULL);
	}
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb < 0)
	{
		list = (char *)malloc(nb_l + 1);
		if (!list)
			return (NULL);
		list[0] = '-';
	}
	return (ft_stor_list(list, nb_l, nb));
}

char	*ft_itoa(int n)
{
	int	nb_l;

	nb_l = ft_count_nb(n);
	return (ft_locate_list(nb_l, n));
}
