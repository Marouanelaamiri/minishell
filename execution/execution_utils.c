/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:26 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/10 12:38:19 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void setup_redirections(t_cmd *cmd)
{
	t_redir *redir = cmd->redir;
	int fd;
	bool process_redir;
	
	while (redir)
	{
		process_redir = true;
		if (redir->type == REDIR_IN)
			fd = open(redir->value, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == HEREDOC)
			fd = redir->fd;
		else
			process_redir = false;
		if (process_redir)
		{
			if (fd < 0)
			{
				write(2, "minishell ", 10);
				perror(redir->value);
				exit(1);
			}
			if (redir->type == REDIR_IN || redir->type == HEREDOC)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	redir = redir->next;
	}
}
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
char	*find_executable(char *cmd, t_env *env)
{
	char	**paths;
	char	*env_path;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	  if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
		else
        	return NULL;
    }
	env_path = ft_getenv(env, "PATH");
	if (!env_path)
		return (NULL);
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
char **token_to_av(t_token *token)
{
	size_t count = 0;
	t_token *tmp = token;
	
	if (!token)
		return (NULL);
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	char **av = malloc(sizeof(char *) * (count + 1));
	if (!av)
		return (NULL);
	size_t i = 0;
	tmp = token;
	while (tmp)
	{
		av[i] = ft_strdup(tmp->value);
		if (!av[i])
		{
			while (i > 0)
				free(av[--i]);
			return (free(av), NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return ((av[i] = NULL) , av);
}
char **env_list_to_envp(t_env *env)
{
    size_t  count = 0;
    t_env   *cur;
    char   **envp;
    size_t  i;
    cur = env;
    while (cur)
    {
        if (cur->value != NULL)
            count++;
        cur = cur->next;
    }
    envp = malloc((count + 1) * sizeof *envp);
    if (envp == NULL)
        return NULL;
    cur = env;
    i   = 0;
    while (cur)
    {
        if (cur->value != NULL)
        {
            size_t len = ft_strlen(cur->name)+ 1 + ft_strlen(cur->value)+ 1;
            envp[i] = malloc(len);
            if (envp[i] == NULL)
            {
                while (i-- > 0)
                    free(envp[i]);
                return (free(envp), NULL);
            }
            ft_strlcpy(envp[i], cur->name, len);
            ft_strlcat(envp[i], "=",          len);
            ft_strlcat(envp[i], cur->value,  len);
            i++;
        }
        cur = cur->next;
    }
    return((envp[i] = NULL), envp);
}
