/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:03:47 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/29 15:48:36 by malaamir         ###   ########.fr       */
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
    t_token *tok = cmd->args->next;
    char    *path;
    char    *cwd;
	
    if (tok && tok->type == WORD)
        path = tok->value;
    else
        path = ft_getenv(*env, "HOME");

    if (!path)
		return (write(2, "cd: HOME not set\n", 17), 1);
	if (path[0] == '/')
    {
        if (chdir("/") < 0)
			return (perror("cd"), 1);
	}
	
    if (cd_walk_path(path) < 0)
		 return(perror("cd"), 1);
		 
    cwd = getcwd(NULL, 0);
	
    if (!cwd)
		return (perror("getcwd"), 1);
	
    env_set(env, "PWD", cwd);
    free(cwd);
    return 0;
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
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
int	ft_exit(t_cmd *cmd, t_env **env) // need opt
{
	t_token	*arg = cmd->args->next;
	long	status;
	char *s; 

	(void)env;
	printf("exit\n");

	if (!arg)
		exit(0);
	s = arg->value;
	if (*s == '-' || *s == '+')
		s++;
	if (!*s || !ft_isnum(arg->value))
	{
		write(2, "minishell: ", 12);
		write(2, "exit: ", 7);
		write(2, arg->value, ft_strlen(arg->value));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	if (arg->next)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	status = ft_atoi(arg->value);
	status = (status % 256 + 256) % 256;
	_exit((int)status);
}

