/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:26 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/18 14:31:13 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, cmd);
	free(tmp);
	return (result);
}

static char	*check_direct_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_in_path(char *cmd, char *env_path)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_split(paths), NULL);
}

char	*find_executable(char *cmd, t_env *env)
{
	char	*env_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_direct_path(cmd));
	env_path = ft_getenv(env, "PATH");
	if (!env_path)
	{
		if (ft_strchr (cmd, '/'))
			return (check_direct_path(cmd));
		else
			return (ft_strdup(cmd));
	}
	return (search_in_path(cmd, env_path));
}
