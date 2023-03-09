/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:29:33 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/09 12:32:25 by ebelkhei         ###   ########.fr       */
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

# define SPACES 1
# define PIPE 2
# define OPERATOR 3
# define DOUBLE 4
# define SINGLE 5
# define HYPHEN 6
# define WORD 7
# define SINGLE_EXPAND 8

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

int				tokenize(char *line, t_token **tokens);
int				token_mode(char *token);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *ptr);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
int				ft_strlcpy(char *dst, const char *src, int dstsize);
char			*ft_substr(char const *s, unsigned int start, size_t len);
t_token			*ft_lstnew(void *content);
void			ft_lstadd_back(t_token **lst, t_token *new);
void			print_data(t_token *tokens);
int				ft_error(t_token **tokens);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_lstclear(t_token **lst);
void			ft_lstdelone(t_token *lst);
t_token			*ft_lstlast(t_token *lst);
t_token			*ft_lstbeflast(t_token *lst);
int				check_syntax_errors(t_token *token);
void			*parse_env(char **envp, t_env **environment);
int				ft_strchr(const char *str, int c);
t_env			*ft_lstnew_2(void *key, void *value);
void			ft_lstadd_back_2(t_env **lst, t_env *new);
void			print_environment(t_env *tokens);
int				ft_strcmp(const char *s1, const char *s2);
char			*get_expansion(t_env *env, char *key);
char			*ft_strjoin(char *str1, char *str2);
void			expansion(t_token *token, t_env *env, t_token **tokens);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_lstdel(t_token *bef, t_token **current, t_token **tokens);
t_cmd			*ft_lstnew_3(void);
void			ft_lstadd_back_3(t_cmd **lst, t_cmd *new);
int				ft_putendl_fd(char *s, char *str, int fd);
t_cmd			*ft_lstlast2(t_cmd *lst);
int				parse_cmds(t_cmd **cmds, t_token **toks);
void			print_cmd(t_cmd *cmd);
void			del_spaces(t_token *token, t_token **tokens);
int				ft_lstsize(t_token *lst);
void			initialize_cmd(t_cmd *cmd);
void			clear_cmds(t_cmd **cmds);
int				token_mode(char *token);
int				is_separator(char *line);
int				is_expansion_separator(int a);
void			is_operator(t_token *token, t_cmd *cmd);
void			initialize_args(t_token *token, t_cmd *cmd);
void			hyphen_expansion(t_token *token, t_env *env);
void			ft_free(char *str1, char *str2, char *content, char *expansion);
int				ft_isalnum(int argument);
void			ft_trim(t_token *tok);
char			*ft_itoa(int n);
void			ft_lstadd_back_4(t_redirection **lst, t_redirection *new);
t_redirection	*ft_lstnew_4(char *out, int type);
void			ft_lstclear_2(t_redirection **lst);
t_redirection	*ft_lstlast_3(t_redirection *lst);
void			ft_lstdelone_2(t_redirection *lst);
void			*ft_calloc(size_t	n, size_t size);
void			sig_int_handler(int a);
void			sig_quit_handler(int a);
t_exp			*ft_lstnew_5(char *key);
void			ft_lstadd_back_5(t_exp **lst, t_exp *new);
void			ft_lstdel_2(t_env *bef, t_env *current, t_env **tokens);
int				check_for_ambiguous_redirect(t_token *token);
void			var_expansion(t_env *env, char **tok);
char			*to_trim(char const	*s1, char const	*set);
void			tool_1(t_token *tok);
void			tool_2(t_token *tok);
int				ft_strstr(char *big, char *lil, int start, int pos);
char			**wild_cards(char	*wildcard);
char			*my_strchr(const char *str, int c);
void			ft_free_all_mfs(char **str);
void			do_wild_card_expansion(t_token *token, t_token **toks);
void			initialize_vars(char **content, char **tmp, int *i, char *tok);
void			ignore_exp_here_doc(t_token *tok);
int				ft_join(t_token **token, t_token *bef);
int				check_digits(char *str);
int				must_expand(int a, int b);
void			rl_replace_line(const char *s, int n);

#endif
