/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:05:31 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/01 21:54:30 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

# define OUT 0
# define APPEND 1
# define IN 2
# define HERE_DOC 3

typedef struct t_info
{
	int	exit_status;
}	t_info;

#ifndef g_global_data

t_info	g_global_data;

#endif 

typedef struct t_token
{
	char			*content;
	int				type;
	struct t_token	*next;
}	t_token;

typedef struct t_redirection
{
	char					*redirection;
	int						type;
	struct t_redirection	*next;
}	t_redirection;

typedef struct t_cmd
{
	char			**cmd;
	t_redirection	*in;
	t_redirection	*out;
	int				pipe;
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

/*---------builtins---------*/
int		pwd(void);
int		env(t_env *envp);
/// handle cd no arg and with ~ take to home, cd - previous path 
int		cd(t_cmd cmd, t_env*env);
int		echo(char **av);
void	unset(char **key, t_env	*env_vars);
int		export(t_env **env, char	**add);
void	call_builtin(t_env *env_var, t_cmd	*cmd);
int		is_builtin(char *cmd);

/*----------utils----------*/
void	free_env(t_env *env);
void	free_strs(char **str);
// char	*find_path(t_env	env);
char	*find_path(t_env	*env);
void	ft_dprintf(char *format, char *str);
char	**ls_to_arr(t_env *env);
char	*check_path(char	**path, char	**utils);
int		set_in(t_cmd cmd);
int		set_out(t_cmd cmd);
int		herdoc(char *del);

/*---------checking--------*/
void	check(t_cmd *cmd, t_env *env);

/*------single_command-----*/
void	single_cmd(t_cmd *cmd, t_env *env);

/*-----multiple_command----*/
void	even_child(int i, int in, int out, t_pipe p);
void	odd_child(int i, int in, int out, t_pipe p);
void	cmd_checker(t_pipe p, t_cmd cmd, int *io, int i);
void	multiple_cmds(int count, t_cmd *cmd, t_env *env);
int		ft_cmdsize(t_cmd *lst);


#endif