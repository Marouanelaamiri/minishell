/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:26 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/26 16:14:21 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void setup_redirections(t_cmd *cmd)
{
	t_redir *r = cmd->redir;
	int fd;

	while (r)
	{
		if (r->type == REDIR_IN)
		{
			fd = open(r->value, O_RDONLY);
			if (fd < 0)
			{
				perror(r->value);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == REDIR_OUT)
		{
			fd = open(r->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(r->value);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == APPEND)
		{
			fd = open(r->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(r->value);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == HEREDOC)
		{
			fd = heredoc_pipe(r->value);
			if (fd < 0)
			{
				perror(r->value);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		r = r->next;
	}
}
char *find_executable(char *cmd, t_env *env)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd , '/'))
		return (ft_strdup(cmd));
	char *path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	char *dup_path = ft_strdup(path);
	char *token = ft_strtok(dup_path, ":");
	while(token)
	{
		char *full_path = ft_strjoin(token, "/");
		char *executable = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(executable, X_OK) == 0)
		{
			free(dup_path);
			return (executable);
		}
		free(executable);
		token = ft_strtok(NULL, ":");
	}
	free(dup_path);
	return (NULL);
	
}
char **token_to_av(t_token *token)
{
	size_t count = 0;
	t_token *tmp = token;
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
    t_env *cur = env;
    while (cur)
    {
        count++;
        cur = cur->next;
    }
    char **envp = malloc((count + 1) * sizeof *envp);
    if (!envp)
        return NULL;
    cur = env;
    size_t i = 0;
    while (cur)
    {
        size_t len = ft_strlen(cur->name) + 1 + ft_strlen(cur->value) + 1;
        envp[i] = malloc(len);
        if (!envp[i])
        {
            while (i-- > 0)
                free(envp[i]);
            free(envp);
            return NULL;
        }
        ft_strlcpy(envp[i], cur->name, len);
        ft_strlcat(envp[i], "=",      len);
        ft_strlcat(envp[i], cur->value, len);
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
        return -1;
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, delim) == 0)
        {
            free(line);
            break;
        }
        write(fds[1], line, strlen(line));
        write(fds[1], "\n", 1);
        free(line);
    }
    close(fds[1]);
    return fds[0];
}
void	print_export_error(const char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg,                ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
}