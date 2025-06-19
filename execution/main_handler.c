/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:15:45 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/19 17:33:00 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redirect_builtin(t_cmd *cmd,
				int *saved_stdin,
				int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(cmd) != 0)
	{
		ft_update_exit_status(1, 63);
		return (-1);
	}
	return (0);
}

void	handle_single_builtin(t_cmd *cmd, t_env **env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = -1;
	saved_stdout = -1;
	status = 0;
	if (cmd->redir)
	{
		if (redirect_builtin(cmd, &saved_stdin, &saved_stdout) != 0)
			return ;
	}
	status = handle_builtins(cmd, env);
	if (cmd->redir)
	{
		if (saved_stdin != -1)
			dup2(saved_stdin, STDIN_FILENO);
		if (saved_stdout != -1)
			dup2(saved_stdout, STDOUT_FILENO);
		if (saved_stdin != -1)
			close(saved_stdin);
		if (saved_stdout != -1)
			close(saved_stdout);
	}
	ft_update_exit_status(status, 63);
}

static void	exit_on_eof(void)
{
	write(1, "exit\n", 5);
	clear_history();
	gc_malloc(0, 12);
	exit(ft_update_exit_status(0, 0));
}

int	handle_one_line(t_env **env)
{
	struct termios	term;
	char			*line;
	t_cmd			*cmd;
	char			*prompt;

	line = readline("minishell$ ");
	tcgetattr(STDIN_FILENO, &term);
	if (!line)
		exit_on_eof();
	if (*line)
		add_history(line);
	prompt = ft_strdup_gc(line);
	if (!prompt)
		return (gc_malloc(0, 12), 1);
	free(line);
	cmd = ft_build_pipeline(prompt, *env);
	if (!cmd || preprocess_heredocs(cmd, *env) != 0)
		return (fd_cleaner(), gc_malloc(0, 12), 1);
	if (!cmd->next && is_builtin(cmd))
		handle_single_builtin(cmd, env);
	else
		ft_update_exit_status(execute_commands(cmd, *env), 63);
	tcsetattr(STDIN_FILENO, 0, &term);
	fd_cleaner();
	return (gc_malloc(0, 12), 1);
}

void	delim_of_heredoc(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->prev && (current->prev->type == HEREDOC
				|| (current->prev->type == SPCE
					&& current->prev->prev->type == HEREDOC))
			&& current->type == VAR && current->value
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
