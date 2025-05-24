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
parsing/tokenizing/ft_token_utils.c \
parsing/tokenizing/ft_token_space.c \
parsing/tokenizing/ft_token_redir.c \
parsing/tokenizing/ft_token_quotes.c \
parsing/tokenizing/ft_token_pipe.c \
parsing/tokenizing/ft_string_utils.c \
parsing/quotes_check/ft_check_quotes.c \
parsing/parse_cmd/ft_parse_commands.c\
parsing/syntax_checker/ft_syntax_check.c \
parsing/syntax_checker/ft_valid_var.c \
parsing/sig_handler/ft_signal_handler.c \
parsing/expansion/escape_from_dollars.c \
parsing/expansion/starboy_expand.c \
parsing/expansion/starboy_expand2.c \
parsing/expansion/starboy_expand3.c \
parsing/debug_func/ft_debug.c \
parsing/parsing_utils/ft_status.c \
parsing/parsing_utils/ft_ambiguous.c \
parsing/parsing_utils/filed.c \
parsing/memory_management/ft_free.c \

#------------------------------ Object Files ------------------------------------#
OBJ = $(SRC:.c=.o)

#------------------------------ Readline Paths ----------------------------------#
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
LDLIB = -L$(READLINE_LIB) -lreadline

#------------------------------ Compiler and Flags ------------------------------#
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

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
