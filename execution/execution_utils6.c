/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:35:07 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/16 14:34:19 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dot_commands(char **argv)
{
	if (!argv[0])
		return ;
	if (ft_strcmp(argv[0], "..") == 0)
	{
		print_error("..", "command not found");
		free_argv(argv);
		ft_update_exit_status(127, 63);
		exit(127);
	}
	if (ft_strcmp(argv[0], ".") == 0)
	{
		print_error(".", "filename argument required");
		write(2, ".: usage: . filename [arguments]\n", 34);
		free_argv(argv);
		ft_update_exit_status(2, 63);
		exit(2);
	}
}

void	launch_exec(char **argv, t_child_args *args)
{
	char	*path;

	handle_dot_commands(argv);
	if (is_builtin(args->cmd))
		exit(handle_builtins(args->cmd, args->env));
	path = find_executable(argv[0], *(args->env));
	handle_exec_errors(argv, path);
	if (execve(path, argv, args->envp) == -1)
	{
		free_argv(argv);
		if (errno == ENOEXEC)
			exit((free(path), 0));
		perror("execve");
	}
	exit((free(path), 126));
}

void	handle_path_null(char **argv)
{
	char	*target;

	target = argv[0];
	if (!ft_strchr(target, '/'))
	{
		print_error(target, "command not found");
		free_argv(argv);
		ft_update_exit_status(127, 63);
		exit(127);
	}
	if (access(target, F_OK) == -1)
	{
		print_error(target, "No such file or directory");
		free_argv(argv);
		ft_update_exit_status(127, 63);
		exit(127);
	}
	handle_permission_or_directory(target, argv);
}

int	handle_pipe_and_fork(t_cmd *cmd, t_cmd_exec *exec)
{
	int	i;

	if (cmd->next && pipe(exec->pipe_fds) < 0)
	{
		perror("pipe");
		return (ft_update_exit_status(1, 63), 1);
	}
	exec->pids[exec->index] = fork();
	if (exec->pids[exec->index] < 0)
	{
		perror("fork");
		i = 0;
		while (i < exec->index)
		{
			kill(exec->pids[i], SIGTERM);
			i++;
		}
		return (ft_update_exit_status(1, 63), 1);
	}
	return (0);
}

void	setup_after_fork(t_cmd *cmd, t_cmd_exec *exec)
{
	if (exec->read_end != -1)
		close(exec->read_end);
	if (cmd->next)
	{
		close(exec->pipe_fds[1]);
		exec->read_end = exec->pipe_fds[0];
	}
	else
	{
		exec->last_pid = exec->pids[exec->index];
	}
}
