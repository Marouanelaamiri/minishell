/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:03:47 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/06 19:46:40 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_cmd *cmd, t_env **env)
{
	t_token *token = cmd->args->next;
	int newline = 1;

	(void)env;
	if (token && token->type == WORD 
			&& ft_strcmp(token->value, "-n") == 0)
	{
		newline = 0;
		token = token->next;
	}
	while (token)
	{
		if (token->type == WORD)
			printf("%s", token->value);
		token = token->next;
		if (token)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}
int ft_cd(t_cmd *cmd, t_env **env)
{
    t_token *tok;
    char    *path;
    char    *oldcwd;
    char    *newcwd;

    oldcwd = getcwd(NULL, 0);
	tok = cmd->args->next;
    if (!oldcwd)
        return (perror("getcwd"), 1);

    if (tok && tok->type == WORD)
        path = tok->value;
    else
        path = ft_getenv(*env, "HOME");
    if (!path)
        return (free(oldcwd), write(2, "cd: HOME not set\n", 17), 1);
    if (chdir(path) < 0)
        return (perror("cd"), free(oldcwd), 1);
    newcwd = getcwd(NULL, 0);
    if (!newcwd)
        return (perror("getcwd"), free(oldcwd), 1);
    env_set(env, "OLDPWD", oldcwd);
    env_set(env, "PWD",    newcwd);
    return (free(oldcwd), free(newcwd), 0);
}
int ft_pwd(t_cmd *cmd, t_env **env)
{
	char *cwd;
	(void)cmd;
	(void)env;
    cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"), 1);
	printf("%s\n", cwd);
    free(cwd);
	return (0);
}
int ft_unset(t_cmd *cmd, t_env **env)
{
	t_token *token = cmd->args->next;
	while (token)
	{
		if (token->type == WORD)
			env_unset(env, token->value);
		token = token->next;
	}
	return (0);
}
int ft_env(t_cmd *cmd, t_env **env)
{
	t_env *current = *env;
	(void)cmd;
	while(current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
int	ft_exit(t_cmd *cmd, t_env **env)
{
	t_token	*arg = cmd->args->next;
	int		status; 

	(void)env;
	write(1, "exit\n", 5);
	if (!arg)
		exit(g_exit_status);
	if (!ft_isnum(arg->value))
	{
		print_error("minishell: exit: numeric argument required\n", arg->value);
		exit(2);
	}
	if (arg->next)
		return (print_error("minishell: exit: too many arguments\n", arg->value), 1);
	status = ft_atoi(arg->value);
	status = (status % 256 + 256) % 256;
	exit(status);
}

