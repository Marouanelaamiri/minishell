/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:14:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/23 13:51:53 by malaamir         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_status;

// ENV

typedef struct l_env
{
	char			*value;
	char			*name;
	struct l_env	*next;
}			t_env;

// EXECUTE COMMANDS

typedef struct s_cmd_exec
{
	int		index;
	int		read_end;
	int		cmd_count;
	int		pipe_fds[2];
	pid_t	last_pid;
	pid_t	*pids;
}	t_cmd_exec;

// TOKEN & COMMAND

typedef enum e_type
{
	SQUOTE,
	SPCE,
	DQUOTE,
	VAR,
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}			t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	int				quoted;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

typedef struct s_data
{
	t_token		*token;
	t_token		*last_token;
	t_env		*env;
	int			i;
	int			error;
	int			exit_status;
}			t_data;

// REDIRECTIONS

typedef struct s_redir
{
	t_type			type;
	int				fd;
	char			*value;
	int				quoted;
	struct s_redir	*next;
}			t_redir;

// COMMANDS

typedef struct s_cmd
{
	t_token			*args;
	t_redir			*redir;
	struct s_cmd	*next;
}			t_cmd;

// PROCESS

typedef struct s_child_args
{
	t_cmd		*cmd;
	int			input_fd;
	int			*pipe_fds;
	char		**envp;
	t_env		**env;
}			t_child_args;

// HEREDOC

typedef struct s_heredoc
{
	const char		*delim;
	t_env			*env;
	int				quoted;
}			t_heredoc;

// SHARED // 

// helpers
int			ft_atoi(const char *str);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_strndup(const char *src, size_t n);
char		*ft_substr(const char *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isllnum(const char *str);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strrchr(const char *s, int c);
void		*ft_calloc(size_t count, size_t size);
char		*ft_itoa(int n);
int			ft_update_exit_status(int status, int x);
char		*ft_strstr(const char *haystack, const char *needle);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_isspace(char c);
long long	ft_atoll(const char *str);
size_t		count_tokens(t_token *token);

// memory management

void		ft_free_tokens(t_token *tokens);
void		ft_free_redirs(t_redir *redir);
void		ft_free_cmds(t_cmd *cmd);
void		ft_free_env(t_env *env);
void		free_argv(char **av);
void		free_split(char **arr);
void		free_envp(char **envp);

// EXECUTION PART //

// builtins

int			ft_echo(t_cmd *cmd, t_env **env);
int			ft_cd(t_cmd *cmd, t_env **env);
int			ft_pwd(t_cmd *cmd, t_env **env);
int			ft_export(t_cmd *cmd, t_env **env);
int			ft_unset(t_cmd *cmd, t_env **env);
int			ft_env(t_cmd *cmd, t_env **env);
int			ft_exit(t_cmd *cmd, t_env **env);
int			is_builtin(t_cmd *cmd);
int			handle_builtins(t_cmd *cmd, t_env **env);
int			is_valid_id(const char *str);
int			cd_walk_path(const char *path, t_env **env);
void		sort_env_array(t_env **arr);

// builtin utils

int			print_export_list(t_env *env);
t_env		**build_env_array(t_env *env);
void		print_env_array(t_env **arr);
int			handle_one_export(const char *arg, t_env **env);
int			apply_assign(char *copy, t_env **env);
int			apply_append(char *copy, t_env **env);
int			preprocess_heredocs(t_cmd *cmd_list, t_env *env);
void		print_error(const char *cmd, const char *msg);

// exe utils

void		setup_redirections(t_cmd *cmd);
char		*find_executable(char *cmd, t_env *env);
char		**token_to_av(t_token *token);
char		**env_list_to_envp(t_env *env);
int			heredoc_pipe(const char *delim, t_env *env, int quoted);
void		setup_signal(struct sigaction *sa_old);
void		print_eof_warning(const char *delim);
int			handle_line(char *line, const char *delim, int write_fd);
void		check_args(char **argv);
void		wait_for_all_children(pid_t *pids, int total, pid_t last_pid);
void		handle_exec_errors(char **argv, char *path);
pid_t		run_child_process(t_child_args *args);
int			start_command(t_cmd *cmd, t_cmd_exec *exec,
				char **envp, t_env **env);

//exe

int			execute_commands(t_cmd *cmd_list, t_env *env);
int			count_cmds(t_cmd *cmd_list);

// env_utils

t_env		*init_env(char **envp);
int			env_set(t_env **env, const char *name, const char *value);
int			env_unset(t_env **env, const char *name);
char		*ft_getenv(t_env *env_list, const char *name);
void		update_shell_level(t_env **env);
t_env		*handel_null_env(t_env	*head);
char		*build_path(char *oldcwd, char *path);
t_env		*append_env_node(t_env *head, t_env **tail, char *env);
int			update_existing_env(t_env *env, const char *name,
				const char *value);

// main handsling

void		handle_single_builtin(t_cmd *cmd, t_env **env);
int			handle_one_line(t_env **env);
void		delim_of_heredoc(t_token *tokens);

// PARSING PART //

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
void	escape_from_dollars(t_token *t);
void	starboy_expansion(t_token *t, t_env *env);
void	starboy_quote_expansion(t_token *t, t_env *env);
void	starboy_expand_heredoc(char **line, t_env *env);

// signale
void ft_signal_handler(void);

// parsing
void	nodes_join(t_token *tokens);
int ft_syntax_check(t_token *tokens);
int ft_check_quotes(char *input);
int ft_valid_var(t_token *t);
t_cmd *ft_parse_commands(t_token *tokens);
char	*remove_squotes(char *str);
void	remove_empty_tokens(t_token **tokens);
void	clean_hidden_dollars(t_token *tokens);
int	ambiguous_redirection(t_token *tokens);
void field_split_tokens(t_token **tokens);
t_cmd *ft_process_input(char *input, t_env *env);
// debug
void	print_tokens(t_token *token);

// string manipulation
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

# endif
