NAME				= 	minishell

SRCS				=	minishell.c tokenize.c ./lst_functions/ft_lstadd_back_bonus.c \
						./lst_functions/ft_lstnew_bonus.c ./tools/ft_substr.c ./tools/ft_split.c \
						./tools/ft_strdup.c ./tools/ft_strlcpy.c ./tools/ft_strlen.c ./tools/tools.c \
						./tools/ft_strncmp.c ./lst_functions/ft_lstclear_bonus.c ./lst_functions/ft_lstdelone_bonus.c \
						./lst_functions/ft_lstlast_bonus.c ./lst_functions/ft_lstbeflast.c environment.c ./tools/ft_strchr.c \
						./tools/ft_strjoin.c var_expansion.c ./tools/ft_strtrim.c ./lst_functions/ft_lstdel.c ./tools/ft_putendl_fd.c \
						parse_cmds.c ./lst_functions/ft_lstsize_bonus.c tokenizing_tools.c ./tools/tools_2.c ./tools/parsing_tools.c \
						./tools/expansion_tools.c ./tools/ft_isalnum.c ./tools/ft_itoa.c ./tools/ft_calloc.c
						

CC					= 	cc

CFLAGS				=	-Wall -Wextra -Werror -lreadline

all					:  ${NAME}


${NAME}				:  ${SRCS}
						${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean				:
						rm -f ${NAME}

fclean				:  clean

re 					: 	fclean all 