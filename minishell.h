/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:14:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/08 12:03:32 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_exit_status;  // global variable to store exit status
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
	SQUOTE, // string between single quotes
	SPCE, // space
	DQUOTE, // string between double quotes
	VAR, // variable
	WORD, // word
	PIPE, // pipe
	REDIR_IN, // redirection input
	REDIR_OUT, // redirection output
	HEREDOC, // heredoc
	APPEND, // append
}			t_type;

typedef struct s_token
{
	t_type		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

typedef struct s_redir
{
	t_type		type;
	int			fd;
	char			*value;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	t_token *args;
	t_redir *redir;
	struct s_cmd *next;
}			t_cmd;

typedef struct s_data
{
	t_token		*token;
	t_token		*last_token;
	int			i;
	int			error;
}			t_data;

// debug
void	print_tokens(t_token *token);
void	ft_print_cmds(t_cmd *cmd);

// memory management

void	ft_free_tokens(t_token *tokens);
void	ft_free_redirs(t_redir *redir);
void	ft_free_cmds(t_cmd *cmd);
void	ft_free_env(t_env *env);
void	free_argv(char **av);
void	free_split(char **arr);

// string manipulation
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);


// helpers
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strndup(const char *src, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int 	ft_isdigit(int c);
int 	ft_isnum(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);
void 	ft_update_exit_status(int status);
int		ft_get_exit_status(void);
char	*ft_strstr(const char *haystack, const char *needle);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_isspace(char c);

// builtins
int		ft_echo(t_cmd *cmd, t_env **env);
int		ft_cd(t_cmd *cmd, t_env **env);
int		ft_pwd(t_cmd *cmd, t_env **env);
int		ft_export(t_cmd *cmd, t_env **env);
int		ft_unset(t_cmd *cmd, t_env **env);
int		ft_env(t_cmd *cmd, t_env **env);
int		ft_exit(t_cmd *cmd, t_env **env);
int		is_builtin(t_cmd *cmd);
int		handle_builtins(t_cmd *cmd, t_env **env);
int		is_valid_id(const char *str);
int		cd_walk_path(const char *path);
void	sort_env_array(t_env **arr);
 
// builtin utils
int		print_export_list(t_env *env);
t_env	**build_env_array(t_env *env);
void	print_env_array(t_env **arr);
int		handle_one_export(const char *arg, t_env **env);
int		apply_assign(char *copy, t_env **env);
int		apply_append(char *copy, t_env **env);
int		preprocess_heredocs(t_cmd *cmd_list);
void	print_error(const char *cmd, const char *msg);

// exe utils
void	setup_redirections(t_cmd *cmd);
char	*find_executable(char *cmd, t_env *env);
char	**token_to_av(t_token *token);
char	**env_list_to_envp(t_env *env);
int		heredoc_pipe(const char *delim);

//exe
int	execute_cmds(t_cmd *cmd_list, t_env *env);

// env_utils
t_env	*init_env(char **envp);
int		env_set(t_env **env , const char *name, const char *value);
int		env_unset(t_env **env, const char *name);
char	*ft_getenv(t_env *env_list, const char *name);
void	update_shell_level(t_env **env);

// token
t_token	*lst_new_token(t_type type, char *value);
t_token *ft_tokeniz(char *input);
void	lst_add_back_token(t_data *data, t_token *new);
int		ft_handle_quotes(t_data *data, char *input);
int	ft_handle_space(t_data *data, char *input);
int	ft_handle_var(t_data *data, char *input);
int	ft_handle_word(t_data *data, char *input);
int	ft_handle_pipe(t_data *data);
int	ft_handle_redir(t_data *data, char *input);

// expansion
void ft_expand_cmds(t_cmd *cmd_list, t_env *env);
void	escape_from_dollars(t_token *t);
void	starboy_expansion(t_token *t, t_env *env);

// signale
void ft_signal_handler(void);

// parsing

int ft_syntax_check(t_token *tokens);
int ft_check_quotes(char *input);
int ft_valid_var(t_token *t);
t_cmd *ft_parse_commands(t_token *tokens);


# endif