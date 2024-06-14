NAME			=	minishell

LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

RL_DIR			=	./readline
RL_H			=	$(RL_DIR)/libhistory.a
RL_L			=	$(RL_DIR)/libreadline.a

HEADERS			=	-I./include -I$(LIBFT_DIR)/include
LINKERS			=	-Lreadline -lreadline -lncurses
LIBS			=	$(RL_H) $(RL_L) $(LIBFT)

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
CFLAGS			=	-Wall -Werror -Wextra -g
#-fsanitize=address
RM				=	rm -f

SRC_DIR	=	./src
OBJ_DIR	=	./obj

# Sources are all .c files
SRCS	=	main.c \
			cd.c \
			echo.c \
			env.c \
			errors.c \
			exit.c \
			export.c \
			free.c \
			minishell.c \
			pwd.c \
			unset.c \
			utils.c \
			parsing.c \
			split_args.c \
			exec.c \
#			signal.c
			

#env -i ./minishell

OBJS	=	$(addprefix $(OBJ_DIR)/, ${SRCS:.c=.o})

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): rl $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(LINKERS) $(LIBS) $(OBJS) -o $(NAME)

rl:
	@if test $(TEST) = 1 ; then \
		cd readline && ./configure && make ; \
	else \
		echo readline already make ; \
	fi

$(LIBFT):
	@printf $(L)making libft\n$(L)
	@make -s -C $(LIBFT_DIR)
	@printf $(L)libft done\n$(L); 

readline:
	cd $(RL_DIR) && ./configure && $(MAKE)

rm_readline:
	cd $(RL_DIR) && make distclean

# Removes objects
clean:
	@$(RM) -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo $(shell clear)
	@printf $(L)clean ok\n$(L)

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@$(RM) -rf minishell.dSYM
	@rm $(LIBFT)
	@echo $(shell clear)
	@printf $(L)fclean ok\n$(L)

ffclean: rm_readline fclean

run: all
	@./$(NAME)

re: fclean all

.PHONY: all rl run mc readline rm_readline