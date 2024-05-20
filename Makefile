# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:53:47 by jcoquet           #+#    #+#              #
#    Updated: 2024/05/20 11:57:16 by jcoquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRC_DIR = src/

OBJ_DIR = obj/

LIBFT			= ./libft/libft.a
LIBFT_DIR		= ./libft
LIBFT_MAKE		= make -C $(LIBFT_DIR)
LIBFT_CLEAN		= make clean -C $(LIBFT_DIR)
LIBFT_FCLEAN	= make fclean -C $(LIBFT_DIR)

HEADERS =	-I./include -I$(LIBFT_DIR)/include

SRCS =		errors.c \
			cd.c \
			echo.c \
			env.c \
			exit.c \
			export.c \
			pwd.c \
			unset.c \
			free.c \
			main.c \
			minishell.c \
			parsing.c \
			signal.c \
			utils.c \
		
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(HEADERS) -L readline-8.2 -l ncurses readline-8.2/libhistory.a \
readline-8.2/libreadline.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling $(notdir $<)\n"

$(LIBFT):	
	@$(LIBFT_MAKE)
	@$(LIBFT_CLEAN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	
fclean: 	clean
	$(RM) $(NAME)
	@$(LIBFT_FCLEAN)

re: fclean all

.PHONY = all re clean fclean


#in the folder readline make distclean

# add regle export in zshrc
# export LDFLAGS="-L/Users/jcoquet/.brew/opt/readline/lib"
# export CPPFLAGS="-I/Users/jcoquet/.brew/opt/readline/include"
