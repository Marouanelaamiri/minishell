/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:46:06 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/03 20:14:03 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd	*ft_create_cmd(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

// Adds a redirection to the command's redir list
static void	ft_add_redir_to_cmd(t_cmd *cmd, t_type type, char *value)
{
	t_redir *new = malloc(sizeof(t_redir));
	if (!new || !value)
		return;
	new->type = type;
	new->fd = -1;
	new->value = value;
	new->next = NULL;

	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		t_redir *curr = cmd->redir;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

// Adds an argument (token) to the command's args list
static void	ft_add_arg_to_cmd(t_cmd *cmd, t_token *arg)
{
	if (!cmd->args)
		cmd->args = arg;
	else
	{
		t_token *curr = cmd->args;
		while (curr->next)
			curr = curr->next;
		curr->next = arg;
		arg->prev = curr;
	}
}

// Main command parser: converts token list into linked list of t_cmd
t_cmd	*ft_parse_commands(t_token *tokens)
{
	t_cmd *head = NULL;
	t_cmd *last = NULL;
	t_cmd *current = NULL;

	while (tokens)
	{
		// Start a new command if needed
		if (!current)
		{
			current = ft_create_cmd();
			if (!current)
				return (NULL);
			if (!head)
				head = current;
			else
				last->next = current;
		}

		if (tokens->type == PIPE)
		{
			last = current;
			current = NULL;
			tokens = tokens->next;
			continue;
		}

		// Handle redirection
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == HEREDOC || tokens->type == APPEND)
		{
			t_type redir_type = tokens->type;
			tokens = tokens->next;

			if (!tokens || !tokens->value)
				return (NULL); // invalid syntax

			char *file = ft_strdup(tokens->value);
			if (!file)
				return (NULL);
			ft_add_redir_to_cmd(current, redir_type, file);
			tokens = tokens->next;
			continue;
		}

		// Accept these token types as arguments
		if (tokens->type == WORD)
		{
			t_token *arg = malloc(sizeof(t_token));
			if (!arg)
				return (NULL);
			arg->type = tokens->type;
			arg->value = ft_strdup(tokens->value);
			arg->next = NULL;
			arg->prev = NULL;
			ft_add_arg_to_cmd(current, arg);
		}

		tokens = tokens->next;
	}

	return head;
}
