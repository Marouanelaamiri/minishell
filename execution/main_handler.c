/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:15:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/22 11:23:45 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_builtin(t_cmd *cmd, t_env **env)
{
	int	saved_stdout;
	int	status;

	status = 0;
	saved_stdout = -1;
	if (cmd->redir)
	{
		saved_stdout = dup(STDOUT_FILENO);
		setup_redirections(cmd);
	}
	status = handle_builtins(cmd, env);
	if (cmd->redir && saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	ft_update_exit_status(status, 63);
}

int	handle_one_line(t_env **env)
{
    char	*line;
    t_cmd	*cmd;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_update_exit_status(0, 63);
		printf("exit\n");
		return (clear_history(),0);
	}
	if (*line)
		add_history(line);
	cmd = ft_process_input(line, *env);
	free(line);
	if (!cmd)
		return (1);
	if (preprocess_heredocs(cmd, *env) != 0)
		return ((ft_free_cmds(cmd)), 1);
	if (!cmd->next && is_builtin(cmd))
		handle_single_builtin(cmd, env);
	else
		ft_update_exit_status(execute_commands(cmd, *env), 63);
	return ((ft_free_cmds(cmd)), 1);
}

void	delim_of_heredoc(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == VAR && current->value &&
			current->value[1] == '\0' && current->next &&
			(current->next->type == DQUOTE ||
			current->next->type == SQUOTE))
		{
			free(current->value);
			current->value = ft_strdup("");
			if (!current->value)
				return ;
		}
		current = current->next;
	}
}
