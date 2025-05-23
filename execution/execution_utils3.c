/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:10:40 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 15:19:58 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_permission_or_directory(char *target, char **argv)
{
	if (access(target, X_OK) == -1)
	{
		print_error(target, "Permission denied");
		free_argv(argv);
		exit(126);
	}
	if (opendir(target))
	{
		print_error(target, "is a directory");
		free_argv(argv);
		exit(126);
	}
}

void	handle_exec_errors(char **argv, char *path)
{
	char	*target;

	if (path)
		target = path;
	else
		target = argv[0];
	if (access(target, F_OK) == 0)
	{
		handle_permission_or_directory(target, argv);
	}
	if (!path)
	{
		print_error(argv[0], "command not found");
		free_argv(argv);
		exit(127);
	}
}

static void	loop_free_envp(char **envp, size_t i)
{
	while (i-- > 0)
		free(envp[i]);
	free(envp);
}

static char	*build_env_entry(t_env *env_var)
{
	size_t	len;
	char	*entry;

	len = ft_strlen(env_var->name) + ft_strlen(env_var->value) + 2;
	entry = malloc(len);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, env_var->name, len);
	ft_strlcat(entry, "=", len);
	ft_strlcat(entry, env_var->value, len);
	return (entry);
}

char	**env_list_to_envp(t_env *env)
{
	char	**envp;
	size_t	count;
	size_t	i;

	count = count_env_vars(env);
	envp = malloc((count + 1) * (sizeof (*envp)));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = build_env_entry(env);
			if (!envp[i])
				return (loop_free_envp(envp, i), NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
