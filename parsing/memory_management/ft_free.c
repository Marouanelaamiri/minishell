/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:26:23 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/24 17:32:50 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_free_tokens(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void ft_free_redirs(t_redir *redir)
{
	t_redir *tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void ft_free_cmds(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
			ft_free_tokens(tmp->args);
		if (tmp->redir)
			ft_free_redirs(tmp->redir);
		free(tmp);
	}
}

void	ft_free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}
void    free_envp(char **envp)
{
    int i;

    if (!envp)
        return ;
    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}
void free_argv(char **av)
{
	size_t i = 0;
	while (av && av[i])
		free(av[i++]);
	free(av);
}
void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	check_args(char **argv)
{
	if (!argv || !argv[0] || !argv[0][0])
	{
		free_argv(argv);
		exit(0);
	}
}
