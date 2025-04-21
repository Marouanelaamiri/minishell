# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaamir <malaamir@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 15:01:51 by malaamir          #+#    #+#              #
#    Updated: 2025/04/21 12:55:56 by malaamir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
execution/builtin.c \
execution/builtin_utils.c \
execution/env_utils.c \
parsing/tokenizing/ft_tokenize.c \
parsing/syntax_check/ft_syntax_check.c\
#------------------------------Object Files------------------------------------#
OBJ = $(SRC:.c=.o)
#------------------------------Compiler and Flages------------------------------#
CC = cc

CFLAGS = -Wall -Wextra -Werror
#------------------------------Includes and Exuctables--------------------------#
NAME = minishell

#------------------------------Rules---------------------------------------------#
all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
#------------------------------Clean---------------------------------------------#
clean :
	rm -f $(OBJ)
	
fclean : clean
	rm -f $(NAME)
#------------------------------Rebuild--------------------------------------------#
re : fclean all
