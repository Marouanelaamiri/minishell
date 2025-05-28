/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:15:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/28 15:45:26 by malaamir         ###   ########.fr       */
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
		if (setup_redirections(cmd) != 0)
		{
			ft_update_exit_status(1, 63);
			return ;
		}
	}
	status = handle_builtins(cmd, env);
	if (cmd->redir && saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	ft_update_exit_status(status, 63);
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

int	handle_one_line(t_env **env)
{
	char	*line;
	t_cmd	*cmd;
	char	*prompt;

	line = readline("minishell$ ");
	if (!line)
		return (ft_update_exit_status(0, 63), printf("exit\n"),
			clear_history(), gc_malloc(0, 12), 0);
	if (*line)
		add_history(line);
	prompt = ft_strdup_gc(line);
	if (!prompt)
		return (gc_malloc(0, 12), 1);
	free(line);
	cmd = process_input(prompt, *env);
	if (!cmd || preprocess_heredocs(cmd, *env) != 0)
		return (gc_malloc(0, 12), 1);
	if (!cmd->next && is_builtin(cmd))
		handle_single_builtin(cmd, env);
	else
		ft_update_exit_status(execute_commands(cmd, *env), 63);
	fd_cleaner();
	return (gc_malloc(0, 12), 1);
}

void	delim_of_heredoc(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == VAR && current->value
			&& current->value[1] == '\0' && current->next
			&& (current->next->type == DQUOTE
				|| current->next->type == SQUOTE))
		{
			current->value = ft_strdup_gc("");
			if (!current->value)
				return ;
		}
		current = current->next;
	}
}
