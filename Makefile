SRCS	= $(wildcard ./builtins/*.c) main.c $(wildcard ./execution/*.c) $(wildcard ./parsing/*.c) $(wildcard ./parsing/tools/*.c) $(wildcard ./parsing/lst_functions/*.c)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -lreadline 

NAME	= minishell

MK_FILE	= Makefile

# LIBFT	= ./libft/libft.a

all		: $(NAME)

$(NAME) : $(SRCS) $(MK_FILE)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean	:
		rm -rf $(NAME)

fclean	:
		rm -rf $(NAME)

re		: fclean re
