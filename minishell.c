/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/19 17:29:28 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd *ft_process_input(char *input, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	// lexer
	tokens = ft_tokenize(input);
	if (!tokens)
		return (NULL);
	
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
		// 1) Tokenize

		// 3) Dispatch built‑ins
		if (cmd)
			status = handle_builtins(cmd, &env);
		// if (status < 0)
		// {
		//     // 4) Not a built‑in → external execution (you implement execute_cmds)
		//     status = execute_cmds(cmd, env);
		// }
	}
	free_env(env);
	return 0;
}
