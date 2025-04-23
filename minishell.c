/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:57:50 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/23 17:58:58 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

static t_cmd *ft_process_input(char *input, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd_list;
		
	if (!ft_check_quotes(input)) // check for unclosed quotes
	{
		ft_update_exit_status(258);
		return (NULL);
	}
	// lexer
	tokens = ft_tokenize(input); // tokenize input
	if (!tokens)
	{
		ft_update_exit_status(1);
		return (NULL);
	}
	// print_tokens(tokens);
	if (!ft_syntax_check(tokens)) // syntax check
	{
		ft_update_exit_status(258);
		// ft_free_tokens(tokens);
		return (NULL);
	}
	// parser
	cmd_list = ft_parse_commands(tokens); // parse commands 
	ft_expand_cmds(cmd_list, env); // expand variables in commands
	
	return (cmd_list);
}

// static void on_exit(void) {
//     char cmd[64];
//     snprintf(cmd, sizeof cmd, "leaks %d", getpid());
//     system(cmd);
// }

int main(int argc, char **argv, char **envp)
{
	// atexit(on_exit);
	t_env  *env = init_env(envp);
	// printf("here : %s\n", env->name);
	// printf("here : %s\n", env->value);
	update_shell_level(&env);
	char   *line;
	int     status = 0;
	t_cmd   *cmd = NULL;

	(void)argc; 
	(void)argv;
	ft_signal_handler(); // set up signal handlers
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_update_exit_status(0);
			printf("exit\n");
			clear_history();
			break;
		}
		if (*line)
			add_history(line);
		cmd = ft_process_input(line, env);
		if (cmd)
		{
			// ft_print_cmds(cmd);
			status = handle_builtins(cmd, &env);
		}
		// if (status < 0)
		// {
		// 	printf("make one lol\n");
		//     // status = execute_cmds(cmd, env);
		// }
	}
	free_env(env);
	return 0;
}