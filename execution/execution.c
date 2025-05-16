/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:26:11 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/16 21:15:17 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void    check_args(char **argv)
{
    if (!argv || !argv[0] || !argv[0][0])
    {
        free_argv(argv);
        exit(0);
    }
}
static void	wait_for_all_children(pid_t *pids, int total, pid_t last_pid)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (pids[i] != last_pid)
			waitpid(pids[i], NULL, 0);
		i++;
	}
}
static pid_t	run_child_process(t_cmd *cmd, int input_fd, int *pipe_fds,
	char **envp, t_env **env)
{
	char	**argv;
	char	*path;

	if (input_fd != -1)
		dup2(input_fd, STDIN_FILENO), close(input_fd);
	if (cmd->next)
		dup2(pipe_fds[1], STDOUT_FILENO),
		close(pipe_fds[0]), close(pipe_fds[1]);
	setup_redirections(cmd);
	argv = token_to_av(cmd->args);
	check_args(argv);
	if (is_builtin(cmd))
		exit(handle_builtins(cmd, env));
	path = find_executable(argv[0], *env);
	if (!path)
		print_error(argv[0], "command not found"),
		free_argv(argv), exit(127);
	if (opendir(path))
		print_error(path, "is a directory"), exit(126);
	execve(path, argv, envp);
	perror("execve");
	free_argv(argv);
	free(path);
	exit(126);
}
static int	start_command(t_cmd *cmd, t_cmd_exec *exec, char **envp, t_env **env)
{
	if (cmd->next && pipe(exec->pipe_fds) < 0)
		return (perror("pipe"), 1);
	exec->pids[exec->index] = fork();
	if (exec->pids[exec->index] < 0)
		return (perror("fork"), 1);
	if (exec->pids[exec->index] == 0)
		run_child_process(cmd, exec->read_end, exec->pipe_fds, envp, env);
	if (exec->read_end != -1)
		close(exec->read_end);
	if (cmd->next)
	{
		close(exec->pipe_fds[1]);
		exec->read_end = exec->pipe_fds[0];
	}
	else
		exec->last_pid = exec->pids[exec->index];
	exec->index++;
	return (0);
}
int	execute_commands(t_cmd *cmd_list, t_env *env)
{
	t_cmd_exec	exec;
	char		**envp;
	t_cmd		*current;
	int			status;

	envp = env_list_to_envp(env);
	if (!envp)
		return (1);
	exec.cmd_count = count_cmds(cmd_list);
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (free_envp(envp), 1);
	exec.read_end = -1;
	exec.index = 0;
	current = cmd_list;
	while (current)
	{
		if (start_command(current, &exec, envp, &env))
			exit(1);
		current = current->next;
	}
	waitpid(exec.last_pid, &status, 0);
	wait_for_all_children(exec.pids, exec.cmd_count, exec.last_pid);
	free(exec.pids);
	return (free_envp(envp),WEXITSTATUS(status));
}
