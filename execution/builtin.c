/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:03:47 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/26 16:18:31 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_cmd *cmd, t_env **env)
{
	t_token *token = cmd->args->next;
	int newline = 1;

	(void)env;
	if (token && token->type == WORD && ft_strcmp(token->value, "-n") == 0)
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
    t_token *tok       = cmd->args->next;
    char    *path;
    char     oldcwd[PATH_MAX];
    char     newcwd[PATH_MAX];

    if (tok && tok->type == WORD)
        path = tok->value;
    else
        path = ft_getenv(*env, "HOME");

    if (!path)
		return( write(2, "cd: HOME not set\n", 17), 1);
    if (!getcwd(oldcwd, sizeof oldcwd))
		return (perror("cd"), 1);
    if (path[0] == '/')
    {
        if (chdir("/") < 0)
        {
            perror("cd");
            return 1;
        }
    }
    if (cd_walk_path(path) < 0)
    {
        perror("cd");
        chdir(oldcwd);
        return 1;
    }
    if (!getcwd(newcwd, sizeof newcwd))
    {
        return (chdir(oldcwd), 0);
        return 0;
    }
    env_set(env, "OLDPWD", oldcwd);
    env_set(env, "PWD",    newcwd);
    return 0;
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
    t_token *tok = cmd->args->next;
    int      status = 0;
    if (tok == NULL)
    {
        size_t n;
		size_t i;
        t_env **arr = env_to_array(*env, &n);
		
        if (!arr)
			return 1;
        sort_env_array(arr, n);
        i = 0;
        while (i < n)
        {
            char *name  = arr[i]->name;
            char *value = arr[i]->value;

            if (value && *value)
                printf("declare -x %s=\"%s\"\n", name, value);
            else
                printf("declare -x %s\n", name);

            i++;
        }
        free(arr);     
        return 0;
    }            
    while (tok)
    {
        char *pluseq = ft_strstr(tok->value, "+=");
        char *eq     = NULL;
        char *name;
        char *value;
        char *old;
        if (pluseq)
        {
            *pluseq = '\0';
            name   = tok->value;
            value  = pluseq + 2;
			
            if (!is_valid_id(name))
            {
				print_export_error(name);
                status = 1;
            }
            else
            {
                old = ft_getenv(*env, name);
                if (!old) old = "";
                char *new = ft_strjoin(old, value);
                env_set(env, name, new);
                free(new);
            }
            *pluseq = '+';
        }
        else
        {
            eq = ft_strchr(tok->value, '=');
            if (eq)
            {
                *eq = '\0';
                name  = tok->value;
                value = eq + 1;
                if (!is_valid_id(name))
                {
					print_export_error(name);
                    status = 1;
                }
                else
                {
                    env_set(env, name, value);
                }
                *eq = '=';
            }
            else
            {
                name = tok->value;
                if (!is_valid_id(name))
                {
					print_export_error(name);
                    status = 1;
                }
                else if (ft_getenv(*env, name) == NULL)
					env_set(env, name, ""); 
            }
        }
        tok = tok->next;
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
	exit((int)status);
}

