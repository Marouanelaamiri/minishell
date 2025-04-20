/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/20 18:56:15 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd *ft_process_input(char *input, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	(void)env;
	(void)cmd_list;
	
	if (!ft_check_quotes(input))
		return (NULL);
	// lexer
	tokens = ft_tokenize(input);
	if (!tokens)
		return (NULL);
	if (!ft_syntax_check(tokens))
	{
		// ft_free_tokens(tokens);
		return (NULL);
	}
	return (NULL);
}
void print_tokens(t_token *token)
{
	while (token)
	{
		printf("  [Type: %d, Value: \"%s\"]\n", token->type, token->value);
		token = token->next;
	}
}

void print_cmd_list(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
		printf("Command %d:\n", ++i);
		print_tokens(cmd->args);
		cmd = cmd->next;
	}
}

// --- Main Shell Loop ---
int main(int argc, char **argv, char **envp)
{
	t_env  *env = init_env(envp);
	char   *line;
	int     status = 0;
	t_cmd   *cmd = NULL;

	(void)argc; (void)argv;
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
		cmd = ft_process_input(line, env);
		// 3) Dispatch built‑ins
		if (cmd)
			status = handle_builtins(cmd, &env);
		// if (status < 0)
		// {
		//     // 4) Not a built‑in → external execution (you implement execute_cmds)
		//     status = execute_cmds(cmd, env);
		// }
	}
	return 0;
}
