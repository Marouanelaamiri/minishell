/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:16:53 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/22 15:15:36 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_cmd *cmd, t_env **env)
{
	t_token *token = cmd->args->next;
	int newline = 1;
	char *str;

	(void)env;
	if (token && token->type == WORD && ft_strcmp(token->value, "-n") == 0)
	{
		newline = 0;
		token = token->next;
	}
	while (token)
	{
		if (token->type == WORD)
		{
			str = strip_quotes(token->value);
			printf("%s", str);
			free(str);
		}
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
	t_token *token = cmd->args->next;
	char *path;
	char cwd[PATH_MAX];
	int ret;
	
	if (token != NULL && token->type == WORD)
		path = token->value;
	else
		path = ft_getenv(*env, "HOME");
	
	if (path == NULL)
		return((write(2, "cd: HOME not set\n",18) ,1));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("getcwd"), 1);
	ret = chdir(path);
	if (ret < 0)
		return (perror("cd"), 1);
	env_set(env, "OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		env_set(env, "PWD", cwd);
	else
		return (perror("getcwd"), 1);
	return (0);
}
int ft_pwd(t_cmd *cmd, t_env **env)
{
	char cwd[PATH_MAX];
	(void)cmd;
	(void)env;
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("getcwd"), 1);
	printf("%s\n", cwd);
	return (0);
}
int ft_export(t_cmd *cmd, t_env **env)
{
    t_token *token = cmd->args->next;
    int      status = 0;
    if (token == NULL)
        return ft_env(cmd, env);
    while (token)
    {
        char *equal = ft_strchr(token->value, '=');
        char *name;
        char *value;
        if (equal == NULL)
        {
            name  = token->value;
            value = NULL;
        }
        else
        {
            *equal = '\0';
            name  = token->value;
            value = equal + 1;
        }
        if (is_valid_id(name) == 0)
        {
			write(2, "minishell", 10);
			write(2, " : export: `", 13);
			write(2 , token->value, ft_strlen(token->value));
			write(2, "': not a valid identifier\n", 26);
            status = 1;
        }
        else
        {
            char *clean_name  = strip_quotes(name);
            char *clean_value = NULL;
            if (value)
                clean_value = strip_quotes(value);
            else
                clean_value = ft_strdup("");
            env_set(env, clean_name, clean_value);
            free(clean_name);
            free(clean_value);
        }
        if (equal)
            *equal = '=';
        token = token->next;
    }

    return status;
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


int	ft_exit(t_cmd *cmd, t_env **env)
{
	t_token	*arg = cmd->args->next;
	long	status;

	(void)env;
	printf("exit\n");

	if (!arg)
		exit(0);

	if (!ft_isnum(arg->value))
	{
		write(2, "exit: numeric argument required\n", 33);
		exit(255);
	}
	if (arg->next)
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	status = ft_atoi(arg->value);
	status = (status % 256 + 256) % 256;
	exit((int)status);
}

