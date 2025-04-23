/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:50:20 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/23 12:16:47 by malaamir         ###   ########.fr       */
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
# define PATH_MAX 1024


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

typedef struct s_redir
{
	t_type		type; // REDIR_IN, REDIR_OUT, HEREDOC, APPEND
	char			*value; // file name
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	t_token *args; // head of the token list
	t_redir *redir; // head of the redirection list
	struct s_cmd *next; // next command in the list specified by the pipe
}			t_cmd;

// helpers
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strndup(const char *src, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	ft_isalnum(int c);
int	ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isnum(const char *str);

// builtins

int ft_echo(t_cmd *cmd, t_env **env);
int ft_cd(t_cmd *cmd, t_env **env);
int ft_pwd(t_cmd *cmd, t_env **env);
int ft_export(t_cmd *cmd, t_env **env);
int ft_unset(t_cmd *cmd, t_env **env);
int ft_env(t_cmd *cmd, t_env **env);
int	ft_exit(t_cmd *cmd, t_env **env);
int is_builtin(t_cmd *cmd);
int handle_builtins(t_cmd *cmd, t_env **env);
char *strip_quotes(const char *s);
int is_valid_id(const char *str);
int  cd_walk_path(const char *path);

// env_utils

t_env *init_env(char **envp);
int env_set(t_env **env , const char *name, const char *value);
int env_unset(t_env **env, const char *name);
char *ft_getenv(t_env *env_list, const char *name);
void free_env(t_env *env_list);

// parsing

t_token	*ft_tokenize(const char	*input);
int	ft_syntax_check(t_token *tokens);
int ft_check_quotes(const char *input);
t_cmd	*ft_parse_commands(t_token *tokens);
void ft_signal_handler(void);

# endif