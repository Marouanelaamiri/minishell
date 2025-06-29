#------------------------------ Source Files ------------------------------------#
SRC = minishell.c\
execution/helpers/ft_strcmp.c \
execution/helpers/ft_substr.c \
execution/helpers/ft_atoi.c \
execution/helpers/ft_strchr.c \
execution/helpers/ft_strndup.c \
execution/helpers/ft_strdup.c \
execution/helpers/ft_strlen.c \
execution/helpers/ft_strlcpy.c \
execution/helpers/ft_isalnum.c \
execution/helpers/ft_isllnum.c \
execution/helpers/ft_strjoin.c \
execution/helpers/ft_calloc.c \
execution/helpers/ft_isalpha.c \
execution/helpers/ft_itoa.c \
execution/helpers/ft_strstr.c \
execution/helpers/ft_strlcat.c \
execution/helpers/ft_split.c \
execution/helpers/ft_strrchr.c \
execution/helpers/ft_atoll.c \
execution/ft_export.c \
execution/ft_cd.c \
execution/ft_echo.c \
execution/ft_env.c \
execution/ft_exit.c \
execution/ft_pwd.c \
execution/ft_unset.c \
execution/builtin_utils.c \
execution/builtin_utils2.c \
execution/execution_utils.c \
execution/execution_utils2.c \
execution/execution_utils3.c \
execution/execution_utils4.c \
execution/execution_utils5.c \
execution/execution_utils6.c \
execution/ft_export_utils.c \
execution/env_utils.c \
execution/env_utils2.c \
execution/execution.c \
execution/heredoc.c \
execution/heredoc_utils.c \
execution/main_handler.c \
parsing/tokenizing/ft_tokenize.c \
parsing/tokenizing/ft_token_word.c \
parsing/tokenizing/ft_token_var.c \
parsing/tokenizing/ft_token_var_utils.c \
parsing/tokenizing/ft_token_utils.c \
parsing/tokenizing/ft_token_space.c \
parsing/tokenizing/ft_token_redir.c \
parsing/tokenizing/ft_token_quotes.c \
parsing/tokenizing/ft_token_pipe.c \
parsing/tokenizing/ft_string_utils.c \
parsing/quotes_check/ft_check_quotes.c \
parsing/quotes_check/dquotes_utils.c \
parsing/quotes_check/squotes_utils.c \
parsing/quotes_check/quote_masking.c \
parsing/parse_cmd/ft_parse_commands.c\
parsing/parse_cmd/ft_cmd_utils.c\
parsing/syntax_checker/ft_syntax_check.c \
parsing/sig_handler/ft_signal_handler.c \
parsing/expansion/escape_from_dollars.c \
parsing/expansion/starboy_expand.c \
parsing/expansion/starboy_expand_p2.c \
parsing/expansion/q_dollar_expand.c \
parsing/expansion/q_env_expand.c \
parsing/expansion/starboy_expand3.c \
parsing/expansion/starboy_quote_expand.c \
parsing/expansion/heredoc_utils_env.c \
parsing/expansion/heredoc_utils_number.c \
parsing/expansion/heredoc_utils_question.c \
parsing/expansion/utils_expansion.c \
parsing/parsing_utils/ft_status.c \
parsing/parsing_utils/clean_dollars.c \
parsing/parsing_utils/nodes_join_v1.c \
parsing/parsing_utils/nodes_join_v1_utils.c \
parsing/parsing_utils/nodes_join_v2.c \
parsing/parsing_utils/remove_tokens.c \
parsing/parsing_utils/ft_ambiguous.c \
parsing/parsing_utils/filed.c \
parsing/parsing_utils/ft_split_gc.c \
parsing/parsing_utils/string.c \
parsing/parsing_utils/itoa_gc.c \
parsing/memory_management/ft_free.c \
parsing/memory_management/gc.c \
parsing/main_pars.c \

#------------------------------ Object Files ------------------------------------#
OBJ = $(SRC:.c=.o)

#------------------------------ Readline Paths ----------------------------------#
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
LDLIB = -L$(READLINE_LIB) -lreadline

#------------------------------ Compiler and Flags ------------------------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror 

#------------------------------ Executable --------------------------------------#
NAME = minishell

#------------------------------ Rules -------------------------------------------#
all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[1;32m✅ Compiling complete source code into executable...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) $(LDLIB) -o $(NAME)
	@echo "\033[1;32m🎉 Build successful! You can now run ./minishell\033[0m"
	@echo "\033[1;31m"
	@echo "███╗   ███╗ ██╗███╗   ██╗ ██╗███████╗██╗  ██╗██████╗  ██╗ ██╗"
	@echo "████╗ ████║███║████╗  ██║███║██╔════╝██║  ██║╚════██╗███║███║"
	@echo "██╔████╔██║╚██║██╔██╗ ██║╚██║███████╗███████║ █████╔╝╚██║╚██║"
	@echo "██║╚██╔╝██║ ██║██║╚██╗██║ ██║╚════██║██╔══██║ ╚═══██╗ ██║ ██║"
	@echo "██║ ╚═╝ ██║ ██║██║ ╚████║ ██║███████║██║  ██║██████╔╝ ██║ ██║"
	@echo "╚═╝     ╚═╝ ╚═╝╚═╝  ╚═══╝ ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝  ╚═╝ ╚═╝"
	@echo "\033[0m"

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -I$(READLINE_INCLUDE) -c $< -o $@
	@echo "\033[1;34m🔹 Compiling: $< -> $@\033[0m"

#------------------------------ Cleaning ----------------------------------------#
clean:
	@echo "\033[0;33m🧼 Removing compiled object files to clean up...\033[0m"
	@rm -f $(OBJ)
	@echo "\033[0;32m✔️  Clean complete.\033[0m"

fclean: clean
	@echo "\033[0;31m🗑️ Removing final executable (minishell)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[0;32m✔️  Full clean complete.\033[0m"

re: fclean all
