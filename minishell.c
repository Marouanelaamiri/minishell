/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/04/23 17:57:50 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/23 17:58:58 by sojammal         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Created: 2025/04/13 15:01:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/23 17:47:07 by sojammal         ###   ########.fr       */
=======
/*   Created: 2025/04/23 14:14:55 by malaamir          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/23 17:31:40 by malaamir         ###   ########.fr       */
=======
/*   Updated: 2025/04/23 14:28:02 by malaamir         ###   ########.fr       */
>>>>>>> 1a8796a6b425341a194f576d94b9d8649d953114
>>>>>>> 6a125801a1c8db4a1346cba0381cc7c44c4e51d0
>>>>>>> dda574d69ecba10eaa1b9d79f4592c03409f56be
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
	int ret;
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
<<<<<<< HEAD
		ret = handle_builtins(cmd, &env);
		if (ret > 0)
			status = ret;
		// else
			// status = execute_cmd(cmd, env); // execute the command
=======
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
<<<<<<< HEAD
=======
=======
		if (status < 0)
		{
		    // status = execute_cmds(cmd, env);
		}
>>>>>>> 1a8796a6b425341a194f576d94b9d8649d953114
>>>>>>> 6a125801a1c8db4a1346cba0381cc7c44c4e51d0
>>>>>>> dda574d69ecba10eaa1b9d79f4592c03409f56be
	}
	free_env(env);
	return 0;
}