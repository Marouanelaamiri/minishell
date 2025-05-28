/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:59:31 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/28 15:44:22 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_invalid_id_error(const char *value)
{
	write(2, "minishell: ", 12);
	write(2, "unset :`", 9);
	write(2, value, ft_strlen(value));
	write(2, "': not a valid identifier\n", 27);
}

static void	process_unset_token(t_token *token, t_env **env,
	t_cmd *cmd, int *status)
{
	(void)cmd;
	if (ft_strcmp(token->value, "_") == 0)
		return ;
	if (!is_valid_id(token->value))
	{
		print_invalid_id_error(token->value);
		*status = 1;
	}
	else
		env_unset(env, token->value);
}

int	ft_unset(t_cmd *cmd, t_env **env)
{
	t_token	*token;
	int		status;

	token = cmd->args->next;
	status = 0;
	while (token)
	{
		if (token->type == WORD)
			process_unset_token(token, env, cmd, &status);
		token = token->next;
	}
	return (status);
}
