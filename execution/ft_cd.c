/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:59:03 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 11:52:34 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path(t_token *tok, t_env **env)
{
	if (tok && tok->type == WORD)
		return (tok->value);
	return (ft_getenv(*env, "HOME"));
}

static int	cd_to_root(char *path)
{
	if (path[0] == '/')
	{
		if (chdir("/") < 0)
		{
			perror("cd");
			return (-1);
		}
	}
	return (0);
}

static void	update_path(char **newcwd, char *component)
{
	char	*delim;
	char	*tmp;

	if (ft_strcmp(component, "..") == 0)
	{
		delim = ft_strrchr(*newcwd, '/');
		if (delim && delim != *newcwd)
			*delim = '\0';
		else
			(*newcwd)[1] = '\0';
	}
	else if (ft_strcmp(component, ".") != 0)
	{
		tmp = ft_strjoin(*newcwd, "/");
		free(*newcwd);
		*newcwd = ft_strjoin(tmp, component);
		free(tmp);
	}
}

char	*build_path(char *oldcwd, char *path)
{
	char	*newcwd;
	char	**components;
	int		i;

	newcwd = ft_strdup(oldcwd);
	components = ft_split(path, '/');
	i = 0;
	while (components && components[i])
	{
		update_path(&newcwd, components[i]);
		i++;
	}
	return (free_split(components), newcwd);
}

int	ft_cd(t_cmd *cmd, t_env **env)
{
	t_token	*tok;
	char	*path;
	char	*oldcwd;
	char	*newcwd;

	tok = cmd->args->next;
	oldcwd = getcwd(NULL, 0);
	path = get_path(tok, env);
	if (!path)
		return (free(oldcwd),
			write(2, "cd: HOME not set\n", 17), 1);
	if (cd_to_root(path) < 0
		|| cd_walk_path(path, env) < 0)
		return (free(oldcwd), perror("cd"), 1);
	newcwd = getcwd(NULL, 0);
	if (!newcwd && oldcwd)
		newcwd = build_path(oldcwd, path);
	else if (!newcwd)
		return (free(oldcwd), perror("getcwd"), 1);
	env_set(env, "OLDPWD", oldcwd);
	env_set(env, "PWD", newcwd);
	free(oldcwd);
	free(newcwd);
	return (0);
}
