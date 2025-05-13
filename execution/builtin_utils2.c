/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:51:48 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/13 19:52:43 by malaamir         ###   ########.fr       */
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
				return(free(cwd), 1);
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
int	cd_walk_path(const char *path)
{
	char	**segments;
	int		i;
	int		ret;

	if (!path || path[0] == '\0')
		return (0);
	segments = ft_split(path, '/');
	if (!segments)
		return (-1);
	i = 0;
	ret = 0;
	while (segments[i])
	{
		if (!cd_handle_segment(segments[i], &ret))
			break ;
		i++;
	}
	return (free_split(segments), ret);
}