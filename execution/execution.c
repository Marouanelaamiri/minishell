/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:26:11 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/08 14:39:15 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_cmds(t_cmd *cmd_list, t_env *env) // need opt and split
{
    char **envp = env_list_to_envp(env);
    if (!envp)
        return 1;
    int stages = 0;
    t_cmd *cur = cmd_list;
    while (cur)
    {
        stages++;
        cur = cur->next;
    }
    int prev_fd = -1;
    int pipefd[2];
    int created = 0;
    cur = cmd_list;
    while (cur)
    {
        if (cur->next)
        {
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                exit(1);
            }
        }
        pid_t pid = fork();
        if (pid < 0)
			 return (perror("fork"), exit(1), 0);
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cur->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            setup_redirections(cur);
            char **argv = token_to_av(cur->args);
            if (!argv || !argv[0] || !argv[0][0])
			{
				free_argv(argv);
                exit(0);
			}
			if (is_builtin(cur)) 
			{
				int status = handle_builtins(cur, &env);
				free_argv(argv);
				ft_update_exit_status(status);
				exit(status);
			}
            char *path = find_executable(argv[0], env);
            if (!path)
            {
				print_error(argv[0], "command not found");
				free_argv(argv);
            	exit(127);
            }
            execve(path, argv, envp);
            perror("execve");
			free_argv(argv);
			free(path);
            exit(126);
        }
        if (prev_fd != -1)
			close(prev_fd);
        if (cur->next)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        else
			prev_fd = -1;
        created++;
        cur = cur->next;
    }
    int status = 0;
    int waited = 0;
    while (waited < created)
    {
        wait(&status);
        waited++;
    }
    char **e = envp;
    while (*e)
    {
        free(*e);
        e++;
    }
    free(envp);
    return WEXITSTATUS(status);
}
