#------------------------------ Source Files ------------------------------------#
SRC = minishell.c\
execution/helpers/ft_strcmp.c \
execution/helpers/is_num.c \
execution/helpers/ft_substr.c \
execution/helpers/ft_atoi.c \
execution/helpers/ft_strchr.c \
execution/helpers/ft_strndup.c \
execution/helpers/ft_strdup.c \
execution/helpers/ft_strlen.c \
execution/helpers/ft_strlcpy.c \
execution/helpers/ft_isalnum.c \
execution/helpers/ft_isnum.c \
execution/helpers/ft_strjoin.c \
execution/helpers/ft_calloc.c \
execution/helpers/ft_isalpha.c \
execution/helpers/ft_itoa.c \
execution/helpers/ft_strstr.c \
execution/helpers/ft_strlcat.c \
execution/builtin.c \
execution/ft_export.c \
execution/builtin_utils.c \
execution/env_utils.c \
execution/execution_utils.c \
execution/execution.c \
parsing/tokenizing/ft_tokenize.c \
parsing/syntax_check/ft_syntax_check.c\
parsing/parse_cmd/ft_parse_commands.c\
parsing/sig_handler/ft_signal_handler.c \
parsing/expansion/ft_expand_cmds.c \
parsing/debug_func/ft_debug.c \
parsing/parsing_utils/ft_status.c \
parsing/memory_management/ft_free.c \

#------------------------------ Object Files ------------------------------------#
OBJ = $(SRC:.c=.o)

#------------------------------ Readline Paths ----------------------------------#
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
LDLIB = -L$(READLINE_LIB) -lreadline

#------------------------------ Compiler and Flags ------------------------------#
CC = gcc
CFLAGS = -Wall -Wextra -Werror# -g -fsanitize=address

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

.PHONY: all clean fclean re banner
