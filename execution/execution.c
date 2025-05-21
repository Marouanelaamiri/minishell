/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:02:37 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/21 11:26:54 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (free_envp(envp), WEXITSTATUS(status));
}
