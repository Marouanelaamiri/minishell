<<<<<<< HEAD
=======

>>>>>>> 1a8796a6b425341a194f576d94b9d8649d953114
#------------------------------Source Files------------------------------------#
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
execution/builtin.c \
execution/builtin_utils.c \
execution/env_utils.c \
parsing/tokenizing/ft_tokenize.c \
parsing/syntax_check/ft_syntax_check.c\
parsing/parse_cmd/ft_parse_commands.c\
parsing/sig_handler/ft_signal_handler.c \
parsing/expansion/ft_expand_cmds.c \
parsing/debug_func/ft_debug.c \
parsing/parsing_utils/ft_status.c \
#------------------------------Object Files------------------------------------#
OBJ = $(SRC:.c=.o)
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
LDLIB = -L$(READLINE_LIB) -lreadline
#------------------------------Compiler and Flages------------------------------#
CC = cc

CFLAGS = -Wall -Wextra -Werror
#------------------------------Includes and Exuctables--------------------------#
NAME = minishell

#------------------------------Rules---------------------------------------------#
all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIB) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I$(READLINE_INCLUDE) -c $< -o $@
#------------------------------Clean---------------------------------------------#
clean :
	rm -f $(OBJ)
	
fclean : clean
	rm -f $(NAME)
#------------------------------Rebuild--------------------------------------------#
re : fclean all
