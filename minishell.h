/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:29:33 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/02 18:50:57 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "exec.h"
# include <readline/readline.h>
# include <readline/history.h>

// OPERATORS MACROS
# define OUT 0
# define APPEND 1
# define IN 2
# define HERE_DOC 3

# define SPACE 1
# define PIPE 2
# define OPERATOR 3
# define DOUBLE 4
# define SINGLE 5
# define HYPHEN 6
# define WORD 7
# define LEAKS system("leaks minishell");

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

// typedef struct t_info
// {
// 	int	exit_status;
// }	t_info;

// #ifndef g_global_data

// t_info	g_global_data;

// #endif 

// typedef struct t_token
// {
// 	char			*content;
// 	int				type;
// 	struct t_token	*next;
// }	t_token;

// typedef struct t_redirection
// {
// 	char					*redirection;
// 	int						type;
// 	struct t_redirection	*next;
// }	t_redirection;

// typedef struct t_cmd
// {
// 	char			**cmd;
// 	t_redirection	*in;
// 	t_redirection	*out;
// 	int				pipe;
// 	struct t_cmd	*next;
// }	t_cmd;

// typedef struct t_env
// {
// 	char			*key;
// 	char			*value;
// 	struct t_env	*next;
// }	t_env;

int		tokenize(char *line, t_token **tokens);
int		token_mode(char *token);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *ptr);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token	*ft_lstnew(void *content);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	print_data(t_token *tokens);
int		ft_error(t_token **tokens);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_lstclear(t_token **lst);
void	ft_lstdelone(t_token *lst);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstbeflast(t_token *lst);
int		check_syntax_errors(t_token *token);
void	*parse_env(char **envp, t_env **environment);
int		ft_strchr(const char *str, int c);
t_env	*ft_lstnew_2(void *key, void *value);
void	ft_lstadd_back_2(t_env **lst, t_env *new);
void	print_environment(t_env *tokens);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_expansion(t_env *env, char *key);
char	*ft_strjoin(char *str1, char *str2);
void	expansion(t_token *token, t_env *env, t_token **tokens);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_lstdel(t_token *bef, t_token **current, t_token **tokens);
t_cmd	*ft_lstnew_3(void);
void	ft_lstadd_back_3(t_cmd **lst, t_cmd *new);
int		ft_putendl_fd(char *s, char *str, int fd);
t_cmd	*ft_lstlast2(t_cmd *lst);
int		parse_cmds(t_cmd **cmds, t_token **toks);
void	print_cmd(t_cmd *cmd);
void	del_spaces(t_token *token, t_token **tokens);
int		ft_lstsize(t_token *lst);
void	initialize_cmd(t_cmd *cmd);
void	clear_cmds(t_cmd **cmds);
int		token_mode(char *token);
int		is_separator(char *line);
int		is_expansion_separator(int a);
void	set_operator(t_token *token, t_redirection **redirection, int type);
void	is_operator(t_token *token, t_cmd *cmd);
void	initialize_args(t_token *token, t_cmd *cmd);
void	hyphen_expansion(t_token *token, t_env *env);
void	ft_free(char *str1, char *str2);
int		ft_isalnum(int argument);
void	ft_trim(t_token *tok);
char	*ft_itoa(int n);
void	ft_lstadd_back_4(t_redirection **lst, t_redirection *new);
t_redirection	*ft_lstnew_4(char *out, int type);
void	ft_lstclear_2(t_redirection **lst);
void	*ft_calloc(size_t	n, size_t size);
char	*ft_strnstr(const char	*big, const char	*lil, size_t	len);
// int		ft_lstsize(t_token *lst);
// t_token	*ft_lstlast(t_token *lst);
// void	ft_lstadd_front(t_token **lst, t_token *new);
// void	ft_lstiter(t_token *lst, void (*f)(void *));
// t_token	*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *));

#endif