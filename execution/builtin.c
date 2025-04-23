/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:16:53 by malaamir          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/23 15:28:08 by sojammal         ###   ########.fr       */
=======
/*   Updated: 2025/04/23 15:36:10 by malaamir         ###   ########.fr       */
>>>>>>> 1a8796a6b425341a194f576d94b9d8649d953114
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
			str = ft_strdup(token->value);
<<<<<<< HEAD
			// str = strip_quotes(token->value);
=======
>>>>>>> 1a8796a6b425341a194f576d94b9d8649d953114
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
<<<<<<< HEAD
        else
        {
            char *clean_name  = ft_strdup(name);
            char *clean_value = NULL;
            if (value)
                clean_value = ft_strdup(value);
            else
                clean_value = ft_strdup("");
            env_set(env, clean_name, clean_value);
            free(clean_name);
            free(clean_value);
        }
=======
      else
	  {
		env_set(env, name, value);
	  }
>>>>>>> 1a8796a6b425341a194f576d94b9d8649d953114
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

