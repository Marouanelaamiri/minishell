/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:26:11 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/18 13:25:35 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	spawn_child_process(t_cmd *cmd, t_cmd_exec *exec,
	char **envp, t_env **env)
{
	t_child_args	args;

	args.cmd = cmd;
	args.input_fd = exec->read_end;
	args.pipe_fds = exec->pipe_fds;
	args.envp = envp;
	args.env = env;
	run_child_process(&args);
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
	ft_signal_handler();
}

static void	handle_input_pipe(t_child_args *args)
{
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
}

pid_t	run_child_process(t_child_args *child_ctx)
{
	char	**argv;
	int		redir_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_input_pipe(child_ctx);
	redir_status = setup_redirections(child_ctx->cmd);
	if (redir_status != 0)
		exit(1);
	argv = token_to_av(child_ctx->cmd->args);
	check_args(argv);
	launch_exec(argv, child_ctx);
	return (-1);
}

int	start_command(t_cmd *cmd, t_cmd_exec *exec,
					char **envp, t_env **env)
{
	if (handle_pipe_and_fork(cmd, exec))
		return (1);
	if (exec->pids[exec->index] == 0)
		spawn_child_process(cmd, exec, envp, env);
	setup_after_fork(cmd, exec);
	exec->index++;
	return (0);
}
