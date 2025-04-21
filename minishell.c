/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/21 12:59:08 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_cmd *ft_process_input(char *input, t_env *env)
// {
// 	t_token	*tokens;
// 	t_cmd	*cmd_list;

// 	(void)env;
// 	(void)cmd_list;
	
// 	if (!ft_check_quotes(input))
// 		return (NULL);
// 	// lexer
// 	tokens = ft_tokenize(input);
// 	if (!tokens)
// 		return (NULL);
// 	if (!ft_syntax_check(tokens))
// 	{
// 		// ft_free_tokens(tokens);
// 		return (NULL);
// 	}
// 	return (NULL);
// }
// void print_tokens(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("  [Type: %d, Value: \"%s\"]\n", token->type, token->value);
// 		token = token->next;
// 	}
// }

// void print_cmd_list(t_cmd *cmd)
// {
// 	int i = 0;
// 	while (cmd)
// 	{
// 		printf("Command %d:\n", ++i);
// 		print_tokens(cmd->args);
// 		cmd = cmd->next;
// 	}
// }

// // --- Main Shell Loop ---
// int main(int argc, char **argv, char **envp)
// {
// 	t_env  *env = init_env(envp);
// 	char   *line;
// 	int     status = 0;
// 	t_cmd   *cmd = NULL;

// 	(void)argc; (void)argv;
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			clear_history();
// 			break;
// 		}
// 		if (*line)
// 			add_history(line);
// 		cmd = ft_process_input(line, env);
// 		// 3) Dispatch built‑ins
// 		if (cmd)
// 			status = handle_builtins(cmd, &env);
// 		// if (status < 0)
// 		// {
// 		//     // 4) Not a built‑in → external execution (you implement execute_cmds)
// 		//     status = execute_cmds(cmd, env);
// 		// }
// 	}
// 	return 0;
// }

static t_token *tokenize(const char *line)
{
    t_token *head = NULL, *tail = NULL;
    char *copy = strdup(line), *word, *saveptr;
    word = strtok_r(copy, " ", &saveptr);
    while (word)
    {
        t_token *tok = malloc(sizeof *tok);
        tok->type  = WORD;
        tok->value = strdup(word);
        tok->next  = NULL;
        if (!head) head = tok; else tail->next = tok;
        tail = tok;
        word = strtok_r(NULL, " ", &saveptr);
    }
    free(copy);
    return head;
}

// --- Build a single-command list (no actual parsing of pipes/redirs yet) ---
static t_cmd *build_cmd_list(t_token *tokens)
{
    if (!tokens) return NULL;
    t_cmd *cmd = malloc(sizeof *cmd);
    cmd->args = tokens;
    cmd->next = NULL;
    return cmd;
}

// --- Free functions ---
static void free_tokens(t_token *tok)
{
    t_token *next;
    while (tok)
    {
        next = tok->next;
        free(tok->value);
        free(tok);
        tok = next;
    }
}
static void free_cmds(t_cmd *cmd)
{
    // if you extend to multiple cmds, traverse and free each->args with free_tokens
    free(cmd);
}

// --- Main Shell Loop ---
int main(int argc, char **argv, char **envp)
{
    t_env  *env;
    char   *line;
    int     status;
    int     last_status = 0;

    (void)argc; (void)argv;
    env = init_env(envp);

    while (1)
    {
        line = readline("minishell$ ");
        if (!line)  // EOF / Ctrl‑D
            break;

        if (*line)
            add_history(line);

        // 1) Lex + parse into a single cmd
        t_token *tokens = tokenize(line);
        free(line);
        t_cmd   *cmd    = build_cmd_list(tokens);

        if (cmd && cmd->args)
        {
            // 2) Builtin?
            if (is_builtin(cmd))
                status = handle_builtins(cmd, &env);
            else
            {
                // 3) External command(s)
				printf("make one lol\n");
                // status = execute_cmds(cmd, &env);
            }
            // last_status = status;
        }

        // 4) Clean up
        free_tokens(tokens);
        free_cmds(cmd);
    }

    // Clean exit
    printf("exit\n");
    free_env(env);
    return last_status;
}
