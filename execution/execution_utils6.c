/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:35:07 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/25 15:35:57 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dot_commands(char **argv)
{
	if (!argv[0])
		return ;
	if (ft_strcmp(argv[0], "..") == 0)
	{
		print_error("..", "command not found");
		free_argv(argv);
		exit(127);
	}
	if (ft_strcmp(argv[0], ".") == 0)
	{
		print_error(".", "filename argument required");
		write(2, ".: usage: . filename [arguments]\n", 34);
		free_argv(argv);
		exit(2);
	}
}

void	launch_exec(char **argv, t_child_args *args)
{
	char	*path;

	handle_dot_commands(argv);
	if (is_builtin(args->cmd))
		exit(handle_builtins(args->cmd, args->env));
	path = find_executable(argv[0], *(args->env));
	if (!path)
	{
		print_error(argv[0], "command not found");
		free_argv(argv);
		exit(127);
	}
	handle_permission_or_directory(path, argv);
	if (execve(path, argv, args->envp) == -1)
	{
		free_argv(argv);
		if (errno == ENOEXEC)
			exit((free(path), 0));
		perror("execve");
	}
	exit((free(path), 126));
}
