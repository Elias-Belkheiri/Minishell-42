/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:05:31 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 22:34:45 by hhattaki         ###   ########.fr       */
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

#ifndef g_global_data

t_info	g_global_data;

#endif 

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

//add ambegious or whatever that shit is

/*---------builtins---------*/
int		pwd(void);
int		env(t_env *envp);
/// handle cd no arg and with ~ take to home, cd - previous path 
int		cd(t_cmd cmd, t_env*env);
int		echo(char **av);
int		ft_exit(char **arg);
int		unset(char **key, t_env	**env_vars);
int		export(t_env **env, char	**add);
int		call_builtin(t_env **env_var, t_cmd	*cmd);
int		is_builtin(char *cmd);
int		find_herdoc(t_cmd *cmd, t_env *env);
int		check_if_exported(char *add, int r);
void	add_new(t_env **env, int r, char *add, t_env *new);

/*----------utils----------*/
void	free_env(t_env *env);
void	free_strs(char **str);
char	*find_path(t_env	*env);
void	ft_dprintf(char *format, char *str);
char	**ls_to_arr(t_env *env);
char	*check_path(char	**path, char	**utils);
int		set_in(int i, t_cmd cmd, int herdoc);
int		set_out(t_cmd cmd);
int		herdoc(char *del, t_env *env, int should_expand);
void	check_pipe(t_pipe *p, int i);
int		is_alphanum(char *s);
int		ft_wait(int *id, int i, t_pipe *p);

/*---------checking--------*/
void	check(t_cmd *cmd, t_env **env);
void	check_if_dir(char	*name);

/*------single_command-----*/
void	single_cmd(t_cmd *cmd, t_env *env);

/*-----multiple_command----*/
void	even_child(int in, int out, t_pipe p);
void	odd_child(int in, int out, t_pipe p);
void	cmd_checker(t_pipe p, t_cmd cmd, int *io, int i);
void	multiple_cmds(int count, t_cmd *cmd, t_env **env);
int		ft_cmdsize(t_cmd *lst);

#endif