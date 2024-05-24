# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcoquet <jcoquet@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 07:32:04 by jcoquet           #+#    #+#              #
#    Updated: 2024/05/24 16:34:17 by jcoquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

LIBFT			=	libft.a
LIBFT_DIR		=	libft/

RL_DIR			=	readline/
RL_H			=	libhistory.a
RL_L			=	libreadline.a

#		config		#

# version = \"$(shell cat .config/version)\"

USER = $(shell whoami)
PWD  = \"$(shell pwd)\"

ifeq ($(shell uname -s), Darwin)
    BIN_DIR = \"/Users/$(USER)/Mini_bin/\"
    L = "
else
    BIN_DIR = \"/home/$(USER)/Mini_bin/\"
    L = '
endif


ifeq ($(shell test -d /Users/$(USER)/.brew/opt/readline; echo $$?), 0)
    BREW = .brew
else ifeq ($(shell test -d /Users/$(USER)/homebrew/opt/readline; echo $$?), 0)
    BREW = homebrew
endif

TEST = $(shell test -e readline/libreadline.a ; echo "$$?")

# Compiler and flags
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -Iinclude/ -g
#-fsanitize=address
RM				=	rm -f

# Sources are all .c files
SRCS	=	src/main.c \
			src/cd.c \
			src/echo.c \
			src/env.c \
			src/errors.c \
 			src/exit.c \
			src/export.c \
			src/free.c \
 			src/minishell.c \
 			src/pwd.c \
 			src/signal.c \
			src/unset.c \
			src/utils.c \
			# src/parsing.c \
 			src/split_args.c \
			

#env -i ./minishell

OBJS	=	$(SRCS:.c=.o)

all: rl libft $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) -L readline -l readline -l ncurses \
	$(RL_DIR)$(RL_H) $(RL_DIR)$(RL_L) -o $(NAME)

rl:
	@if test $(TEST) = 1 ; then \
		cd readline && ./configure && make ; \
	else \
		echo readline all ready make ; sleep 2; \
	fi

libft:
	@printf $(L)making libft\n$(L)
	@make -s -C $(LIBFT_DIR)
	@printf $(L)libft done\n$(L); sleep 2; 

readline:
	cd $(RL_DIR) && ./configure && $(MAKE)

rm_readline:
	cd $(RL_DIR) && make distclean


# Removes objects
clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR)	clean
	@echo $(shell clear)
	@printf $(L)clean ok\n$(L)

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@$(RM) -fr minishell.dSYM 
	@make -C $(LIBFT_DIR)     fclean
	@echo $(shell clear)
	@printf $(L)fclean ok\n$(L)

ffclean: rm_readline fclean

run: all
	@./$(NAME)

re: fclean all

cp:
	cp supp.txt /tmp


.PHONY: all libft run mc readline rm_readline