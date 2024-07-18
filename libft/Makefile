NAME	:= libft.a
CFLAGS 	+= -Wall -Wextra -Werror
SRCDIR 	:= ./src
OBJDIR	:= ./obj
HEADERS	:= -I./include

SRCS	= ft_is.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	  	ft_strlcpy.c ft_strlcat.c ft_to.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_put.c ft_lstnew.c ft_lstlast.c ft_lstsize.c ft_lstadd.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstremove.c \
		ft_loopadd.c ft_free_split.c get_next_line.c ft_is2.c ft_printf.c \
		printers1.c printers2.c
OBJS	:= $(addprefix $(OBJDIR)/, ${SRCS:.c=.o})

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
