/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:05:31 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/09 00:20:20 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>

# define OUT 0
# define APPEND 1
# define IN 2
# define HERE_DOC 3
# define IS_PIPE -2
# define START 1
# define END 2

typedef struct t_exp
{
	char			*key;
	struct t_exp	*next;
}	t_exp;

typedef struct t_info
{
	int		exit_status;
	t_exp	*exported_vars;
}	t_info;

# ifndef G_GLOBAL_DATA

t_info	g_global_data;

# endif 

typedef struct t_token
{
	char			*content;
	int				type;
	int				expanded;
	struct t_token	*next;
}	t_token;

typedef struct t_redirection
{
	char					*redirection;
	int						should_expand;
	int						type;
	struct t_redirection	*next;
}	t_redirection;

typedef struct t_cmd
{
	char			**cmd;
	t_redirection	*in;
	t_redirection	*out;
	int				pipe;
	int				err;
	struct t_cmd	*next;
}	t_cmd;

typedef struct t_env
{
	char			*key;
	char			*value;
	struct t_env	*next;
}	t_env;

typedef struct s_pipe
{
	int	p1[2];
	int	p2[2];
}	t_pipe;

typedef struct s_utils
{
	t_pipe	p;
	int		*her;
	int		io[2];
	int		size;
}	t_utils;

/*---------builtins---------*/
int		pwd(void);
int		env(t_env *envp);
int		cd(t_cmd cmd, t_env*env);
int		echo(char **av);
int		ft_exit(char **arg);
int		unset(char **key, t_env	**env_vars);
int		export(t_env **env, char	**add);
int		call_builtin(t_env **env_var, t_cmd	*cmd);
int		is_builtin(char *cmd);
int		find_heredoc(t_cmd *cmd, t_env *env);
int		check_if_exported(char *add, int r);
void	print_export(t_env **env);
int		set_node(char *add, int r, t_env *new);
void	plus_none_existed_var(t_env **env, int r, char *add);

/*----------utils----------*/
void	free_env(t_env *env);
void	free_strs(char **str);
char	*find_path(t_env	*env);
void	ft_dprintf(char *format, char *str);
char	**ls_to_arr(t_env *env);
char	*check_path(char	**path, char	**utils);
int		is_alphanum(char *s);
int		ft_wait(int *id, int i, t_pipe *p);
char	**to_return(DIR *dir, char *cwd, char **files);
char	*my_strchr(const char *str, int c);
int		ft_cmdsize(t_cmd *lst);
void	free_utils(int *utils, pid_t *id);
int		free_them(char **hold);
int		exist_in_env(t_env **env, char *add);

/*--------in_out_utils-------*/
void	get_old_fd(int in, t_env **env_vars, t_cmd *cmd);
int		heredoc(char *del, t_env *env, int should_expand);
void	check_pipe(t_pipe *p, int i);
int		set_in(int i, t_cmd cmd, int heredoc);
int		set_out(t_cmd cmd);

/*---------checking--------*/
void	check(t_cmd *cmd, t_env **env);
void	check_if_dir(char	*name);

/*------single_command-----*/
void	single_cmd(t_cmd *cmd, t_env *env);
void	set_for_single_command(t_cmd *cmd, t_env *env);

/*-----multiple_command----*/
void	even_child(int in, int out, t_pipe p);
void	odd_child(int in, int out, t_pipe p);
void	cmd_checker(t_pipe p, t_cmd cmd, int *io, int i);
void	multiple_cmds(int count, t_cmd *cmd, t_env **env);
int		*open_heredocs(int count, t_cmd *cmd, t_env *env);
void	cmd_type(t_utils *utils, int i, t_cmd *cmd, t_env **env);
void	child_process(t_cmd cmd, t_env *env, int i, t_utils *utils);

/*----------errors--------*/
void	file_error(int in, t_cmd cmd);

/*-------additional-------*/
char	*ft_strnstr(const char	*big, const char	*lil, size_t	len);
void	set_operator(t_token *token, t_redirection **redirection, int type);

#endif