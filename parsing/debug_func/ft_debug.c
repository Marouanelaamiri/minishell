/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:21:02 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/16 23:12:24 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static const char *get_token_type_name(t_type type)
{
	if (type == WORD) return "WORD";
	if (type == DQUOTE) return "DQUOTE";
	if (type == SQUOTE) return "SQUOTE";
	if (type == VAR) return "VAR";
	if (type == SPCE) return "SPCE";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN (<)";
	if (type == REDIR_OUT) return "REDIR_OUT (>)";
	if (type == HEREDOC) return "HEREDOC (<<)";
	if (type == APPEND) return "APPEND (>>)";
	return "UNKNOWN";
}

static void print_args(t_token *args)
{
	t_token *current = args;
	int i = 0;

	while (current)
	{
		printf("    [Arg %d]\n", i++);
		printf("      Type:   %-12s\n", get_token_type_name(current->type));
		printf("      Value:  \"%s\"\n", current->value);
		current = current->next;
	}
	if (i == 0)
		printf("    (No arguments)\n");
}

static void print_redirs(t_redir *redir)
{
	t_redir *current = redir;
	int i = 0;

	while (current)
	{
		printf("    [Redir %d]\n", i++);
		printf("      Type:   %-12s\n", get_token_type_name(current->type));
		printf("      Target: \"%s\"\n", current->value);
		current = current->next;
	}
	if (i == 0)
		printf("    (No redirections)\n");
}

void ft_print_cmds(t_cmd *cmds)
{
	int i = 0;

	printf("\n========== 🧵 Command List ==========\n");

	while (cmds)
	{
		printf("\n🔹 Command #%d\n", i++);
		printf("  ↪ Arguments:\n");
		print_args(cmds->args);

		printf("  ↪ Redirections:\n");
		print_redirs(cmds->redir);

		if (cmds->next)
			printf("  │\n  ▼\n");
		cmds = cmds->next;
	}
	printf("\n========== ✅ End of Commands ==========\n\n");
}



void	print_tokens(t_token *current)
{
	const char *types[] = {
		[WORD] = "WORD",
		[PIPE] = "PIPE",
		[REDIR_IN] = "REDIR_IN",
		[REDIR_OUT] = "REDIR_OUT",
		[HEREDOC] = "HEREDOC",
		[APPEND] = "APPEND",
		[SPCE] = "SPCE",
		[VAR] = "VAR",
		[SQUOTE] = "SQUOTE",
		[DQUOTE] = "DQUOTE"
	};

	int index = 0;
	while (current)
	{
		printf("Index: %d\n", index);
		// if (current->type >= 0 && current->type <= DQUOTE)
		printf("  Type:   %s\n", types[current->type]);
		// else
		// 	printf("  Type:   UNKNOWN (%d)\n", current->type);
		printf("  Value:  %s\n", current->value);
		current = current->next;
		index++;
	}
}

