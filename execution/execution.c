/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:26:11 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/24 18:10:24 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_cmds(t_cmd *cmd_list, t_env *env)
{
    // 1) Build envp array
    char **envp = env_list_to_envp(env);
    if (!envp)
        return 1;

    // 2) Count stages and prepare
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

    // 3) Fork each stage
    cur = cmd_list;
    while (cur)
    {
        // if not last, create a pipe
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
        {
            perror("fork");
            exit(1);
        }

        if (pid == 0)
        {
            // CHILD
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
            if (!argv)
                exit(1);
            char *path = find_executable(argv[0], env);
            if (!path)
            {
                write(2, argv[0], ft_strlen(argv[0]));
                write(2, ": command not found\n", 20);
                _exit(127);
            }
            execve(path, argv, envp);
            perror("execve");
            _exit(126);
        }

        // PARENT
        if (prev_fd != -1)
        {
            close(prev_fd);
        }
        if (cur->next)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        else
        {
            prev_fd = -1;
        }

        created++;
        cur = cur->next;
    }

    // 4) Wait for all children
    int status = 0;
    int waited = 0;
    while (waited < created)
    {
        wait(&status);
        waited++;
    }

    // 5) Cleanup envp
    char **e = envp;
    while (*e)
    {
        free(*e);
        e++;
    }
    free(envp);

    return WEXITSTATUS(status);
}
