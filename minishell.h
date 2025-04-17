/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:48 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/17 15:05:49 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>


# define BUFFER_SIZE 1024
# define MAX_ARGS 100
# define PATH_MAX 4096


// ENV
typedef struct l_env
{
	char			*value; // "PATH"
	char			*name; // "/usr/bin:/bin"
	struct l_env	*next;
}			t_env;


// TOKEN & COMMAND
typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}			t_type;

typedef struct s_token
{
	t_type		type;
	char			*value;
	struct s_token	*next;
}			t_token;

typedef struct s_cmd
{
	t_token *args; // head of the token list
	struct s_cmd *next;
}			t_cmd;

// helpers
int ft_strcmp(const char *s1, const char *s2);
int	is_numeric(const char *str);
char **simple_split(char *input);



// builtins

int ft_echo(t_cmd *cmd, t_env **env);
int ft_cd(t_cmd *cmd, t_env **env);
int ft_pwd(t_cmd *cmd, t_env **env);
int ft_export(t_cmd *cmd, t_env **env);
int ft_unset(t_cmd *cmd, t_env **env);
int ft_env(t_cmd *cmd, t_env **env);
int	ft_exit(t_cmd *cmd, t_env **env);

// env_utils

t_env *init_env(char **envp);
int env_set(t_env **env , const char *name, const char *value);
int env_unset(t_env **env, const char *name);
char *ft_getenv(t_env *env_list, const char *name);
void free_env(t_env *env_list);

// parsing

int handle_builtins(t_cmd *cmd, t_env **env);

# endif