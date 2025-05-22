/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:48:53 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/22 11:10:58 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

// static void on_exit1(void)
// {
//     char cmd[128];
//     snprintf(cmd, sizeof cmd, "leaks %d", getpid());
//     system(cmd);
// }

static void ft_blinding_lights(char *input)
{
    int        n;
    char    temp;
    char    *res;

    res = input;
    n = 0;
    while (res[n])
    {
        if (res[n] == '"' || res[n] == '\'')
        {
            temp = res[n];
            n++;
            if (res[n] == '\0')
                break ;
            while (res[n])
            {
                if (res[n] == temp)
                    break ;
                res[n] *= -1;
                n++;
            }
        }
        if (res[n])
            n++;
    }
}

static void ft_after_hours(t_token *t)
{
    t_token *current = t;
    while (current)
    {
        if (current->type == DQUOTE || current->type == SQUOTE || current->type == WORD)
        {
            if (current->value)
                ft_blinding_lights(current->value);
        }
        current = current->next;
    }
}

void	free_node(t_token *node)
{
	if (!node)
		return ;
	if (node)
	{
		free(node->value);
		free(node);
	}
}

void	nodes_join_part2(t_token *tokens)
{
	t_token *current = tokens;
	t_token *tmp;
	char *joined;

	while (current && current->next)
	{
		if (current->type == WORD && current->next->type == WORD)
		{
			joined = ft_strjoin(current->value, current->next->value);
			if (!joined)
				return ; // handle malloc failure
			free(current->value);
			current->value = joined;

			tmp = current->next;
			current->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = current;
			free_node(tmp);
			continue;
		}
		current = current->next;
	}
}

void	delim_of_heredoc(t_token *tokens)
{
	t_token	*current;

	current = token;
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

static t_cmd *ft_process_input(char *input, t_env *env)
{
    if (!ft_check_quotes(input))
    {
        ft_update_exit_status(258, 63);
        return NULL;
    }
	ft_blinding_lights(input);
    t_token *tokens = ft_tokeniz(input);
    if (!tokens)
    {
		ft_update_exit_status(258, 63);
        return NULL;
    }
	ft_after_hours(tokens);
    if (!ft_syntax_check(tokens))
    {
        ft_update_exit_status(258, 63);
        ft_free_tokens(tokens);
        return NULL;
    }
	escape_from_dollars(tokens);
	delim_of_heredoc(tokens);
	starboy_expansion(tokens, env);
	// print_tokens(tokens);
	if (ambiguous_redirection(tokens))
	{
		ft_update_exit_status(1, 63);
		ft_free_tokens(tokens);
		return NULL;
	}
	nodes_join(tokens);
	nodes_join_part2(tokens);
	remove_empty_tokens(&tokens);
	clean_hidden_dollars(tokens);
	field_split_tokens(&tokens);
	if (!tokens)
	{
		ft_update_exit_status(258, 63);
		return NULL;
	}
    t_cmd *cmd_list = ft_parse_commands(tokens);
    ft_free_tokens(tokens);
    return cmd_list;
}

static void	handle_single_builtin(t_cmd *cmd, t_env **env)
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

static int  handle_one_line(t_env **env)
{
    char  *line;
    t_cmd *cmd;

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
int  main(int argc, char **argv, char **envp)
{
    // atexit(on_exit1);
    t_env *env;

    (void)argc;
    (void)argv;
    env = init_env(envp);
    env_unset(&env, "OLDPWD");
    update_shell_level(&env);
    ft_signal_handler();
    while (handle_one_line(&env))
        ;
    ft_free_env(env);
    return (g_exit_status);
}
