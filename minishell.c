/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/17 15:06:52 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    t_env  *env = init_env(envp);
    char   *line;
    int     status;

    (void)argc; (void)argv;
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)  // EOF or Ctrl‑D
            break;
        if (*line)
            add_history(line);

        // 1) Tokenize
        t_token *tokens = tokenize(line);
        free(line);

        // 2) Build simple cmd list
        t_cmd *cmd = build_cmd_list(tokens);
        if (!cmd || !cmd->args)
        {
            free_tokens(tokens);
            free_cmds(cmd);
            continue;
        }

        // 3) Dispatch built‑ins
        status = handle_builtins(cmd, &env);
        // if (status < 0)
        // {
        //     // 4) Not a built‑in → external execution (you implement execute_cmds)
        //     status = execute_cmds(cmd, env);
        // }

        // 5) Clean up
        free_tokens(tokens);
        free_cmds(cmd);
    }

    printf("exit\n");
    free_env(env);
    return 0;
}
