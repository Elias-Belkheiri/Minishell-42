.SILENT: $(NAME)

SRCS	= $(wildcard ./builtins/*.c) main.c $(wildcard ./execution/*.c) $(wildcard ./parsing/*.c) $(wildcard ./parsing/tools/*.c) $(wildcard ./parsing/lst_functions/*.c)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -lreadline
NAME	= minishell

MK_FILE	= Makefile

# OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

# .c.o	:
# 		$(CC) $(CFLAGS) -c $(SRCS) -o $(NAME)

$(NAME) : $(SRCS) $(MK_FILE)
		# stty -echoctl
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		echo $(NAME) is created!

clean	:
		rm -rf $(OBJS)

fclean	: clean
		rm -rf $(NAME)
		echo $(NAME) is deleted

re		: fclean all
