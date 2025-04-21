/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:46:06 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/20 21:59:09 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd *ft_create_cmd(void)
{
	t_cmd *cmd;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	ft_add_token_to_cmd(t_cmd *cmd, t_token *new_token)
{
	t_token *current = cmd->args;
	if (!cmd->args)
		cmd->args = new_token;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

t_cmd	*ft_parse_commands(t_token *tokens)
{
	t_cmd *head = NULL;
	t_cmd *last = NULL;
	t_cmd *current_cmd = NULL;

	while (tokens)
	{
		if (!current_cmd)
		{
			current_cmd = ft_create_cmd();
			if (!head)
				head = current_cmd;
			else 
				last->next = current_cmd;
		}
		if (tokens->type == PIPE)
		{
			last = current_cmd;
			current_cmd = NULL;
		}
		else
		{
			t_token *copy = malloc(sizeof(t_token));
			copy->type = tokens->type;
			copy->value = ft_strdup(tokens->value);
			copy->next = NULL;
			ft_add_token_to_cmd(current_cmd, copy);
		}
		tokens = tokens->next;
	}
	return (head);
}