/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:02:37 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:47 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_signal_exit(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_update_exit_status(130, 63);
		return (130);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		ft_update_exit_status(131, 63);
		return (131);
	}
	ft_update_exit_status(128 + sig, 63);
	return (128 + sig);
}

static int	wait_and_cleanup(t_cmd_exec *exec, char **envp)
{
	int	status;
	int	exit_code;

	if (exec->last_pid > 0)
		waitpid(exec->last_pid, &status, 0);
	else
		status = (ft_update_exit_status(0, 0) << 8);
	wait_for_all_children(exec->pids, exec->cmd_count, exec->last_pid);
	free(exec->pids);
	free_envp(envp);
	if (WIFSIGNALED(status))
		return (handle_signal_exit(status));
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		ft_update_exit_status(exit_code, 63);
		return (exit_code);
	}
	return (1);
}

static int	handle_command_loop(t_cmd *cmd_list, t_cmd_exec *exec,
					char **envp, t_env **env)
{
	t_cmd	*current;
	int		ret;

	current = cmd_list;
	while (current)
	{
		if ((!current->args || !current->args[0].value
				|| current->args[0].value[0] == '\0')
			&& !current->redir && current->next == NULL)
		{
			write(2, "minishell: : command not found\n", 31);
			ft_update_exit_status(127, 63);
			current = current->next;
			continue ;
		}
		ret = start_command(current, exec, envp, env);
		if (ret != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	execute_commands(t_cmd *cmd_list, t_env *env)
{
	t_cmd_exec	exec;
	char		**envp;
	int			ret;

	envp = env_list_to_envp(env);
	if (!envp)
		return (1);
	exec.cmd_count = count_cmds(cmd_list);
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (free_envp(envp), 1);
	exec.read_end = -1;
	exec.index = 0;
	ret = handle_command_loop(cmd_list, &exec, envp, &env);
	if (ret != 0)
	{
		wait_for_all_children(exec.pids, exec.index, -1);
		free(exec.pids);
		free_envp(envp);
		return (ret);
	}
	return (wait_and_cleanup(&exec, envp));
}

void	fd_cleaner(void)
{
	int	i;

	i = 3;
	while (i < 10240)
	{
		close(i);
		i++;
	}
}
