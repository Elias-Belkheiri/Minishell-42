.SILENT: $(NAME)

SRCS	= $(wildcard ./builtins/*.c) main.c $(wildcard ./execution/*.c) $(wildcard ./parsing/*.c) $(wildcard ./parsing/tools/*.c) $(wildcard ./parsing/lst_functions/*.c)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -lreadline -L/goinfre/ebelkhei/homebrew/opt/readline/lib -I/goinfre/ebelkhei/homebrew/opt/readline/include

NAME	= minishell

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

.c.o	:
		# stty -echoctl
		$(CC) -o $@ -c $<

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		echo $(NAME) is created!

clean	:
		rm -rf $(OBJS)

fclean	: clean
		rm -rf $(NAME)
		echo $(NAME) is deleted

re		: fclean all
