/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:26:11 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 14:59:47 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_args(char **argv)
{
	if (!argv || !argv[0] || !argv[0][0])
	{
		free_argv(argv);
		exit(0);
	}
}

static int	spawn_child_process(t_cmd *cmd, t_cmd_exec *exec,
	char **envp, t_env **env)
{
	t_child_args	args;

	args.cmd = cmd;
	args.input_fd = exec->read_end;
	args.pipe_fds = exec->pipe_fds;
	args.envp = envp;
	args.env = env;
	run_child_process(&args);
	return (0);
}

void	wait_for_all_children(pid_t *pids, int total, pid_t last_pid)
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

pid_t	run_child_process(t_child_args *args)
{
	char	**argv;
	char	*path;

	if (args->input_fd != -1)
	{
		dup2(args->input_fd, STDIN_FILENO);
		close(args->input_fd);
	}
	if (args->cmd->next)
	{
		dup2(args->pipe_fds[1], STDOUT_FILENO);
		close(args->pipe_fds[0]);
		close(args->pipe_fds[1]);
	}
	setup_redirections(args->cmd);
	argv = token_to_av(args->cmd->args);
	check_args(argv);
	if (is_builtin(args->cmd))
		exit(handle_builtins(args->cmd, args->env));
	path = find_executable(argv[0], *(args->env));
	handle_exec_errors(argv, path);
	execve(path, argv, args->envp);
	perror("execve");
	free_argv (argv);
	exit ((free(path), 126));
}

int	start_command(t_cmd *cmd, t_cmd_exec *exec,
	char **envp, t_env **env)
{
	if (cmd->next && pipe(exec->pipe_fds) < 0)
		return (perror("pipe"), 1);
	exec->pids[exec->index] = fork();
	if (exec->pids[exec->index] < 0)
		return (perror("fork"), 1);
	if (exec->pids[exec->index] == 0)
		spawn_child_process(cmd, exec, envp, env);
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
