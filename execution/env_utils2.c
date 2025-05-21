/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:48:18 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/21 15:49:49 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*handel_null_env(t_env	*head)
{
	char	*pwd;
	char	*val;

	head = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd"), exit(1), NULL);
	val = ft_strjoin("PWD=", pwd);
	handle_one_export("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.",
		&head);
	handle_one_export(val, &head);
	handle_one_export("_=/usr/bin/env", &head);
	return (head);
}
