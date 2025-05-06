/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:37:37 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/01 19:23:09 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	ft_valid_format(char *value)
{
	char *var_name;
	
	if (!value || !*value)
		return (0);
	var_name = value + 1;
	if (*var_name == '?')
		return (1);
	while (*var_name)
	{
		if (!is_valid_name(*var_name))
			return (0);
		var_name++;
	}
	return (1);
}

int ft_valid_var(t_token *t)
{
	if (t->type != VAR)
		return 0;
	if (!ft_valid_format(t->value))
	{
		ft_putstr_fd("minishell: syntax error: invalid variable name `", 2);
		ft_putstr_fd(t->value, 2);
		ft_putstr_fd("'\n", 2);
		return 0;
	}
	return 1;
}
