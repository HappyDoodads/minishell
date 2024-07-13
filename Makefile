NAME			:=	minishell

LIBFT_DIR		:=	./libft
LIBFT			:=	$(LIBFT_DIR)/libft.a

RL_URL			:=	https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
RL_ARCH			:=	readline.tar.gz
RL_DIR			:=	./readline
RL_H			:=	$(RL_DIR)/libhistory.a
RL_L			:=	$(RL_DIR)/libreadline.a

HEADERS			:=	-I./include -I$(LIBFT_DIR)/include
LINKERS			:=	-Lreadline -lreadline -lncurses
LIBS			:=	$(RL_H) $(RL_L) $(LIBFT)

# Compiler and flags
CC				:=	gcc
CFLAGS			:=	-Wall -Werror -Wextra -g
RM				:=	rm -rf

SRC_DIR	=	./src
OBJ_DIR	=	./obj

#		config		#

YELLOW	:=	"\001\033[33m\002"
GREEN	:=	"\001\033[32m\002"
BLUE	:=	"\001\033[34m\002"
RST		:=	"\001\e[0m\022\002"

PWD  = \"$(shell pwd)\"

ifeq ($(shell uname -s), Darwin)
    BIN_DIR = \"/Users/$(USER)/Mini_bin/\"
else
    BIN_DIR = \"/home/$(USER)/Mini_bin/\"
endif

ifeq ($(shell test -d /Users/$(USER)/.brew/opt/readline; echo $$?), 0)
    BREW = .brew
else ifeq ($(shell test -d /Users/$(USER)/homebrew/opt/readline; echo $$?), 0)
    BREW = homebrew
endif

#TEST = $(shell test -e readline/libreadline.a ; echo "$$?")

# Sources are all .c files
SRCS	=	main.c \
			cd.c \
			echo.c \
			env.c \
			errors.c \
			exit.c \
			export.c \
			free.c \
			heredoc.c \
			minishell.c \
			pwd.c \
			unset.c \
			fd_utils.c \
			parsing.c \
			redirect_parsing.c \
			split_args.c \
			exec.c \
			substitute.c \
			signal.c
			

#env -i ./minishell

OBJS	=	$(addprefix $(OBJ_DIR)/, ${SRCS:.c=.o})

all: $(NAME)

$(RL_DIR):
	@printf "%breadline-8.2 not found!\n%bFetching...%b" $(YELLOW) $(BLUE) $(RST)
	@curl -s $(RL_URL) --output $(RL_ARCH)
	@tar -xf $(RL_ARCH)
	@mv $(RL_DIR)-8.2 $(RL_DIR)
	@$(RM) $(RL_ARCH)
	@printf "  %bDone!\n%bCompiling...%b" $(GREEN) $(BLUE) $(RST)
	@cd $(RL_DIR) && ./configure >/dev/null && make -s 2>/dev/null \
		&& printf " %bDone!\n%b" $(GREEN) $(RST)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) \
		&& printf "%bCompiling:%b %s\n" $(GREEN) $(RST) $(notdir $<)

$(NAME): $(RL_DIR) $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(LINKERS) $(LIBS) $(OBJS) -o $(NAME)

$(LIBFT):
	@printf "%bCompiling libft...%b" $(BLUE) $(RST)
	@make -C$(LIBFT_DIR) && printf " %bDone!\n%b" $(GREEN) $(RST)

clean:
	@$(RM) $(OBJ_DIR)
	@make -C$(LIBFT_DIR) clean
	@echo $(shell clear)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) minishell.dSYM

ffclean: fclean
	@$(RM) $(RL_DIR)

run: all
	@./$(NAME)

re: fclean all

.PHONY: all clean fclean ffclean run re