/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:02:37 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/28 15:43:44 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wait_and_cleanup(t_cmd_exec *exec, char **envp)
{
	int	status;

	if (exec->last_pid > 0)
		waitpid(exec->last_pid, &status, 0);
	else
		status = (ft_update_exit_status(0, 0) << 8);
	wait_for_all_children(exec->pids, exec->cmd_count, exec->last_pid);
	free(exec->pids);
	free_envp(envp);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	handle_command_loop(t_cmd *cmd_list, t_cmd_exec *exec,
					char **envp, t_env **env)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		if ((!current->args || !current->args[0].value
				|| current->args[0].value[0] == '\0') && !current->redir
			&& current->next == NULL)
		{
			write(2, "minishell: : command not found\n", 31);
			ft_update_exit_status(127, 63);
			current = current->next;
			continue ;
		}
		if (start_command(current, exec, envp, env))
			return (1);
		current = current->next;
	}
	return (0);
}

int	execute_commands(t_cmd *cmd_list, t_env *env)
{
	t_cmd_exec	exec;
	char		**envp;

	envp = env_list_to_envp(env);
	if (!envp)
		return (1);
	exec.cmd_count = count_cmds(cmd_list);
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (free_envp(envp), 1);
	exec.read_end = -1;
	exec.index = 0;
	handle_command_loop(cmd_list, &exec, envp, &env);
	return (wait_and_cleanup(&exec, envp));
}
