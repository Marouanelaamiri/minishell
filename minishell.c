/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/22 22:43:10 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -- debug functions --
// static const char *get_token_type_name(t_type type)
// {
// 	if (type == WORD) return "WORD";
// 	if (type == PIPE) return "PIPE";
// 	if (type == REDIR_IN) return "REDIR_IN";
// 	if (type == REDIR_OUT) return "REDIR_OUT";
// 	if (type == HEREDOC) return "HEREDOC";
// 	if (type == APPEND) return "APPEND";
// 	return "UNKNOWN";
// }
// static void print_tokens(t_token *token)
// {
// 	printf("---- Tokens ----\n");
// 	while (token)
// 	{
// 		printf("[%s] \"%s\"\n", get_token_type_name(token->type), token->value);
// 		token = token->next;
// 	}
// 	printf("----------------\n");
// }
// static void print_redir(t_redir *redir)
// {
//     while (redir)
//     {
//         if (redir->type == REDIR_IN)
//             printf("REDIR_IN: %s ", redir->value);
//         else if (redir->type == REDIR_OUT)
//             printf("REDIR_OUT: %s ", redir->value);
//         else if (redir->type == HEREDOC)
//             printf("HEREDOC: %s ", redir->value);
//         else if (redir->type == APPEND)
//             printf("APPEND: %s ", redir->value);
//         redir = redir->next;
//     }
// }

// static void print_args(t_token *args)
// {
//     while (args)
//     {
//         printf("%s ", args->value);
//         args = args->next;
//     }
// }

// static void ft_print_cmds(t_cmd *cmd)
// {
//     int cmd_number = 1;

//     while (cmd)
//     {
//         printf("[t_cmd %d]\n", cmd_number++);
        
//         // Print args
//         printf("  args: ");
//         if (cmd->args)
//             print_args(cmd->args);
//         else
//             printf("(no args)");
        
//         // Print redir
//         printf("\n  redir: ");
//         if (cmd->redir)
//             print_redir(cmd->redir);
//         else
//             printf("(no redirection)");
        
//         printf("\n\n");
        
//         cmd = cmd->next;
//     }
// }
// // -- end debug functions --
static t_cmd *ft_process_input(char *input, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	(void)env;
	
	if (!ft_check_quotes(input)) // check for unclosed quotes
		return (NULL);
	// lexer
	tokens = ft_tokenize(input); // tokenize input
	if (!tokens)
		return (NULL);
	// print_tokens(tokens);
	if (!ft_syntax_check(tokens)) // syntax check
	{
		// ft_free_tokens(tokens);
		return (NULL);
	}
	// parser
	cmd_list = ft_parse_commands(tokens); // parse commands 
	ft_expand_cmds(cmd_list, env); // expand variables in commands
	
	return (cmd_list);
}


// --- Main Shell Loop ---
int main(int argc, char **argv, char **envp)
{
	t_env  *env = init_env(envp);
	char   *line;
	int     status = 0;
	t_cmd   *cmd = NULL;

	(void)argc; (void)argv;
	ft_signal_handler(); // set up signal handlers
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			clear_history();
			break;
		}
		if (*line)
			add_history(line);
		cmd = ft_process_input(line, env); // process input and return commands list
		// 3) Dispatch built‑ins
		if (cmd)
		{
			// ft_print_cmds(cmd);
			status = handle_builtins(cmd, &env);
		}
		if (status < 0)
		{
		    // 4) Not a built‑in → external execution (you implement execute_cmds)
			printf("make one lol\n");
		    // status = execute_cmds(cmd, env);
		}
	}
	return 0;
}
// --- End of Main Shell Loop ---