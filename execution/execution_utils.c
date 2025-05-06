/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:26 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/06 20:29:00 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// need understanding 
void setup_redirections(t_cmd *cmd)
{
	t_redir *redir = cmd->redir;
	int fd;

	while (redir)
	{
		fd = -1;

		if (redir->type == REDIR_IN)
			fd = open(redir->value, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == HEREDOC)
		{
			fd = redir->fd;
			if (fd < 0)
			{
				perror("heredoc fd");
				exit(1);
			}
		}
		else
		{
			redir = redir->next;
			continue;
		}

		if (fd < 0)
		{
			perror(redir->value);
			exit(1);
		}
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
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
		return (ft_strdup(cmd));
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
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
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
			free(av);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	av[i] = NULL;
	return (av);
}
char **env_list_to_envp(t_env *env)
{
    size_t count = 0;
    t_env  *cur   = env;
    char  **envp;
    size_t i;
    const char *val;

    while (cur)
    {
        count++;
        cur = cur->next;
    }
    envp = malloc((count + 1) * sizeof *envp);
    if (!envp)
        return NULL;
    cur = env;
    i   = 0;
    while (cur)
    {
        if (cur->value != NULL)
            val = cur->value;
        else
            val = "";
        {
            size_t len = ft_strlen(cur->name) + 1 + ft_strlen(val) + 1;
            envp[i] = malloc(len);
            if (!envp[i])
            {
                while (i-- > 0)
                    free(envp[i]);
                free(envp);
                return NULL;
            }
            ft_strlcpy(envp[i], cur->name, len);
            ft_strlcat(envp[i], "=",           len);
            ft_strlcat(envp[i], val,           len);
        }
        i++;
        cur = cur->next;
    }
    envp[i] = NULL;
    return envp;
}
int heredoc_pipe(const char *delim)
{
	int fds[2];
	char *line;

	if (pipe(fds) < 0)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}
int preprocess_heredocs(t_cmd *cmd_list)
{
	t_cmd *cmd = cmd_list;
	while (cmd)
	{
		t_redir *redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->fd = heredoc_pipe(redir->value);
				if (redir->fd < 0)
					return -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return 0;
}
