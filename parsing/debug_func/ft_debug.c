/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:21:02 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/23 22:00:47 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// -- debug functions --
static const char *get_token_type_name(t_type type)
{
	if (type == WORD) return "WORD";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == HEREDOC) return "HEREDOC";
	if (type == APPEND) return "APPEND";
	return "UNKNOWN";
}
void print_tokens(t_token *token)
{
	printf("---- Tokens ----\n");
	while (token)
	{
		printf("[%s] \"%s\"\n", get_token_type_name(token->type), token->value);
		token = token->next;
	}
	printf("----------------\n");
}
static void print_redir(t_redir *redir)
{
    while (redir)
    {
        if (redir->type == REDIR_IN)
            printf("REDIR_IN: %s ", redir->value);
        else if (redir->type == REDIR_OUT)
            printf("REDIR_OUT: %s ", redir->value);
        else if (redir->type == HEREDOC)
            printf("HEREDOC: %s ", redir->value);
        else if (redir->type == APPEND)
            printf("APPEND: %s ", redir->value);
        redir = redir->next;
    }
}

static void print_args(t_token *args)
{
    while (args)
    {
        printf("%s ", args->value);
        args = args->next;
    }
}

void ft_print_cmds(t_cmd *cmd)
{
    int cmd_number = 1;

    while (cmd)
    {
        printf("[t_cmd %d]\n", cmd_number++);
        
        // Print args
        printf("  args: ");
        if (cmd->args)
            print_args(cmd->args);
        else
            printf("(no args)");
        
        // Print redir
        printf("\n  redir: ");
        if (cmd->redir)
            print_redir(cmd->redir);
        else
            printf("(no redirection)");
        
        printf("\n\n");
        
        cmd = cmd->next;
    }
}
// // -- end debug functions --