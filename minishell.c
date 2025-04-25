/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:48:53 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/25 14:53:59 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

static t_cmd *ft_process_input(char *input, t_env *env)
{
    if (!ft_check_quotes(input))
    {
        ft_update_exit_status(258);
        return NULL;
    }

    t_token *tokens = ft_tokenize(input);
    if (!tokens)
    {
        ft_update_exit_status(1);
        return NULL;
    }

    if (!ft_syntax_check(tokens))
    {
        ft_update_exit_status(258);
        ft_free_tokens(tokens);
        return NULL;
    }

    t_cmd *cmd_list = ft_parse_commands(tokens);
    ft_free_tokens(tokens); // free tokens
    ft_expand_cmds(cmd_list, env);
    return cmd_list;
}

// static void on_exit(void)
// {
//     char cmd[64];
//     snprintf(cmd, sizeof cmd, "leaks %d", getpid());
//     system(cmd);
// }

int main(int ac, char **av, char **envp)
{
    // atexit(on_exit);
	(void)ac;
	(void)av;
    t_env *env = init_env(envp);
    update_shell_level(&env);
    ft_signal_handler();

    while (1)
    {
        char *line = readline("minishell$ ");
        if (!line)
        {
            ft_update_exit_status(0);
            printf("exit\n");
            clear_history();
            break;
        }
        if (*line)
            add_history(line);

        t_cmd *cmd = ft_process_input(line, env);
        free(line);

        if (cmd)
        {
            int status = handle_builtins(cmd, &env);
            if (status < 0)
                status = execute_cmds(cmd, env);
            ft_update_exit_status(status);
            ft_free_cmds(cmd);
        }
        // on parse error, fd_exit_status was set; just continue
    }

    free_env(env);
    return g_exit_status;
}
