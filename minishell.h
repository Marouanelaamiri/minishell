/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:14:50 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/20 01:18:15 by sojammal         ###   ########.fr       */
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
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_sig;

typedef struct s_alloc
{
	void			*ptr;
	struct s_alloc	*next;
}	t_alloc;

typedef struct l_env
{
	char			*value;
	char			*name;
	struct l_env	*next;
}			t_env;

typedef struct s_cmd_exec
{
	int		index;
	int		read_end;
	int		cmd_count;
	int		pipe_fds[2];
	pid_t	last_pid;
	pid_t	*pids;
}	t_cmd_exec;

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
	int				hidden;
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

typedef struct s_redir
{
	t_type			type;
	int				fd;
	char			*value;
	int				quoted;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	t_token			*args;
	t_redir			*redir;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_child_args
{
	t_cmd		*cmd;
	int			input_fd;
	int			*pipe_fds;
	char		**envp;
	t_env		**env;
}			t_child_args;

typedef struct s_heredoc
{
	const char		*delim;
	t_env			*env;
	int				quoted;
}			t_heredoc;

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

void		ft_free_env(t_env *env);
void		free_argv(char **av);
void		free_split(char **arr);
void		free_envp(char **envp);

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
void		heredoc_sigint_handler(int sig);

// exe utils
int			setup_redirections(t_cmd *cmd);
char		*find_executable(char *cmd, t_env *env);
char		**token_to_av(t_token *token);
char		**env_list_to_envp(t_env *env);
int			heredoc_pipe(const char *delim, t_env *env, int quoted);
void		check_args(char **argv);
void		wait_for_all_children(pid_t *pids, int total, pid_t last_pid);
void		handle_exec_errors(char **argv, char *path);
pid_t		run_child_process(t_child_args *args);
size_t		count_env_vars(t_env *env);
int			start_command(t_cmd *cmd, t_cmd_exec *exec,
				char **envp, t_env **env);
void		handle_permission_or_directory(char *target, char **argv);
void		launch_exec(char **argv, t_child_args *args);
void		handle_path_null(char **argv);
void		setup_after_fork(t_cmd *cmd, t_cmd_exec *exec);
int			handle_pipe_and_fork(t_cmd *cmd, t_cmd_exec *exec);

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

// main handling
void		handle_single_builtin(t_cmd *cmd, t_env **env);
int			handle_one_line(t_env **env);
void		delim_of_heredoc(t_token *tokens);

/* Token creation and manipulation */
t_token		*lst_new_token(t_type type, char *value);
t_token		*ft_tokeniz(char *input);
void		lst_add_back_token(t_data *data, t_token *new);
void		lst_insert_before(t_token **head, t_token *node,
				t_token *new_token);
void		lst_remove_token(t_token **head, t_token *node);

/* Token handlers during lexing */
int			ft_handle_pipe(t_data *data);
int			ft_handle_quotes(t_data *data, char *input);
int			ft_handle_redir(t_data *data, char *input);
int			ft_handle_space(t_data *data, char *input);
int			ft_handle_var(t_data *data, char *input);
int			ft_handle_word(t_data *data, char *input);

/* Signal handling */
void		ft_signal_handler(void);
void		ft_ctre_c(int sig);

/* Parsing */
int			ambiguous_redirection(t_token *tokens);
void		clean_hidden_dollars(t_token *tokens);
int			ft_check_quotes(char *input);
t_cmd		*ft_parse_commands(t_token *tokens);
void		init_struct(t_cmd **head, t_cmd **last, t_cmd **current);
int			ft_prepare_cmd(t_cmd **current, t_cmd **head, t_cmd **last);
int			ft_handle_word_t(t_token *tokens, t_cmd *current);
int			ft_handle_redir_t(t_token **tokens, t_cmd *current);
void		ft_add_arg_to_cmd(t_cmd *cmd, t_token *arg);
void		ft_add_redir_to_cmd(t_cmd *cmd, t_type type,
				char *value, int quoted);
t_cmd		*ft_create_cmd(void);
char		*remove_squotes(char *str);
char		*remove_dquotes(char *str, int quoted);
void		field_split_tokens(t_token **tokens);
t_cmd		*ft_build_pipeline(char *input, t_env *env);
int			syntax_check(t_token *tokens);
void		unmask_quoted_chars(t_token *token_list);
void		mask_quoted_chars(char *str);

/* Expansion */
void		escape_from_dollars(t_token *token_list);
void		expand_env_dollar(t_token *token, t_env *env);
void		number_before_dollar(t_token *token);
void		process_var_node(t_token *current);
void		starboy_expansion(t_token *token, t_env *env);
void		starboy_quote_expansion(t_token *t, t_env *env);
void		starboy_expand_heredoc(char **line, t_env *env);
void		convert_exit_code(t_token *token);
int			ft_update_exit_status(int status, int x);

/* Expansion helpers */
int			find_dollar(char *str);
int			find_number(char *str);
int			find_question(char *str);
char		*get_variable(char *str, int index);
char		*get_value(t_env *env, char *key_val);
char		*replace_dollar(char *str, int index, t_env *env);
char		*replace_number(char *str, int index);
char		*replace_question(char *str, int index);

/* Heredoc expansion helpers */
int			find_dollar_heredoc(char *str);
int			find_number_heredoc(char *str);
int			find_question_heredoc(char *str);
char		*get_variable_heredoc(char *str, int index);
char		*get_value_heredoc(t_env *env, char *key_val);
char		*replace_dollar_heredoc(char *str, int index, t_env *env);
char		*replace_number_heredoc(char *str, int index);
char		*replace_question_heredoc(char *str, int index);

/* Token joining and cleanup */
void		nodes_join(t_token *tokens);
void		nodes_join_part2(t_token *tokens);
void		remove_empty_tokens(t_token **tokens);

/* Word joining helpers */
void		handle_next(t_token *current, t_token *next);
void		handle_prev(t_token *current, t_token *prev);
void		handle_prev_next(t_token *current, t_token *prev, t_token *next);
void		handle_single(t_token *current);
int			not_redir(t_token *node);

/* Garbage-collected string functions */
void		*gc_malloc(size_t size, int mode);
char		**ft_split_gc(char const *s, char c);
char		*ft_strdup_gc(const char *src);
char		*ft_strdup_full(const char *src, int q);
char		*ft_strdup_spec(const char *src, int *q);
char		*ft_strjoin_gc(const char *s1, const char *s2);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
char		*ft_substr_gc(const char *s, unsigned int start, size_t len);
char		*ft_itoa_gc(int n);

/* Utilities */
int			like_that(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
int			is_redirection(t_type type);
int			ft_error(t_data *data);
int			ft_count_dollars(const char *input, int i);
void		fd_cleaner(void);
int			is_heredoc_delim(t_token *token);

#endif
