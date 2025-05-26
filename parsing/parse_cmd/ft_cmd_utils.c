/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:37:09 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/26 00:38:15 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_create_cmd(void)
{
	t_cmd	*cmd;

	cmd = gc_malloc(sizeof(t_cmd), 63);
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	ft_add_redir_to_cmd(
	t_cmd *cmd, t_type type, char *value, int quoted)
{
	t_redir	*new;
	t_redir	*curr;

	if (!value)
		return ;
	new = gc_malloc(sizeof(t_redir), 63);
	if (!new)
		return ;
	new->type = type;
	new->fd = -1;
	new->value = value;
	new->quoted = quoted;
	new->next = NULL;
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		curr = cmd->redir;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	ft_add_arg_to_cmd(t_cmd *cmd, t_token *arg)
{
	t_token	*curr;

	if (!cmd->args)
		cmd->args = arg;
	else
	{
		curr = cmd->args;
		while (curr->next)
			curr = curr->next;
		curr->next = arg;
		arg->prev = curr;
	}
}

int	ft_prepare_cmd(
	t_cmd **current, t_cmd **head, t_cmd **last)
{
	*current = ft_create_cmd();
	if (!*current)
		return (0);
	if (!*head)
		*head = *current;
	else
		(*last)->next = *current;
	return (1);
}
