/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:59:03 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/13 20:00:48 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(t_cmd *cmd, t_env **env)
{
    t_token *tok;
    char    *path;
    char    *oldcwd;
    char    *newcwd;

    oldcwd = getcwd(NULL, 0);
	tok = cmd->args->next;
    if (!oldcwd)
        return (perror("getcwd"), 1);

    if (tok && tok->type == WORD)
        path = tok->value;
    else
        path = ft_getenv(*env, "HOME");
    if (!path)
        return (free(oldcwd), write(2, "cd: HOME not set\n", 17), 1);
    if (cd_walk_path(path) < 0)
        return (perror("cd"), free(oldcwd), 1);
    newcwd = getcwd(NULL, 0);
    if (!newcwd)
        return (perror("getcwd"), free(oldcwd), 1);
    env_set(env, "OLDPWD", oldcwd);
    env_set(env, "PWD",    newcwd);
    return (free(oldcwd), free(newcwd), 0);
}