/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:51:48 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 12:03:30 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_handle_segment(char *segment, int *ret)
{
	char	*cwd;

	if (ft_strcmp(segment, "..") == 0)
	{
		if (chdir("..") < 0)
		{
			cwd = getcwd(NULL, 0);
			if (cwd && ft_strcmp(cwd, "/") == 0)
				return (free(cwd), 1);
			free(cwd);
			*ret = -1;
			return (0);
		}
	}
	else if (segment[0] != '\0' && ft_strcmp(segment, ".") != 0)
	{
		if (chdir(segment) < 0)
		{
			*ret = -1;
			return (0);
		}
	}
	return (1);
}

static int	cd_fallback(const char *oldcwd, const char *path)
{
	char	*absolute;
	int		ret;

	absolute = build_path((char *)oldcwd, (char *)path);
	if (!absolute)
		return (-1);
	ret = chdir(absolute);
	free(absolute);
	return (ret);
}

static int	cd_process_path_segments(char **segments,
				char *oldcwd, const char *path)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (segments[i])
	{
		if (!cd_handle_segment(segments[i], &ret))
			break ;
		i++;
	}
	if (ret == -1 && errno == EACCES)
		ret = cd_fallback(oldcwd, path);
	return (ret);
}

int	cd_walk_path(const char *path, t_env **env)
{
	char	*oldcwd;
	char	*pwd_env;
	char	**segments;
	int		ret;

	if (!path || path[0] == '\0')
		return (0);
	pwd_env = ft_getenv(*env, "PWD");
	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
	{
		if (!pwd_env)
			return (perror("cd"), -1);
		oldcwd = ft_strdup(pwd_env);
	}
	segments = ft_split(path, '/');
	if (!segments)
		return (free(oldcwd), -1);
	ret = cd_process_path_segments(segments, oldcwd, path);
	free_split(segments);
	return (free(oldcwd), ret);
}
