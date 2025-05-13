/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:59:31 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/13 20:01:48 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_cmd *cmd, t_env **env)
{
	t_token	*token = cmd->args->next;
	int		status = 0;

	while (token)
	{
		if (token->type == WORD)
		{
			if (!is_valid_id(token->value))
			{
				write(2, "minishell: ", 12);
				write(2, "unset :`", 9);
				write (2, token->value , ft_strlen(token->value));
				write(2, "': not a valid identifier\n", 27);
				status = 1;
			}
			else
				env_unset(env, token->value);
		}
		token = token->next;
	}
	return (status);
}