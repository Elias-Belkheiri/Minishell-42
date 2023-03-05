/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:05:18 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/05 17:51:23 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// reads from pipe 1 and write to pipe 2
void	odd_child(int in, int out, t_pipe p)
{
	close(p.p1[1]);
	close(p.p2[0]);
	if (in != IS_PIPE)
	{
		if (in)
		{
			dup2(in, 0);
			close(in);
		}
	}
	else
		dup2(p.p1[0], 0);
	close(p.p1[0]);
	if (out != IS_PIPE)
	{
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
	}
	else
		dup2(p.p2[1], 1);
	close(p.p2[1]);
}
// reads from pipe 2 and writes to pipe 1
void	even_child(int in, int out, t_pipe p)
{
	close(p.p2[1]);
	close(p.p1[0]);
	if (in != IS_PIPE)
	{
		if (in)
		{
			dup2(in, 0);
			close(in);
		}
	}
	else
		dup2(p.p2[0], 0);
	close(p.p2[0]);
	if (out != IS_PIPE)
	{
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
	}
	else
		dup2(p.p1[1], 1);
	close(p.p1[1]);
}

int	ft_wait(int *id, int i, t_pipe *p)
{
	int	status;

	if (p)
	{
		close(p->p1[0]);
		close(p->p1[1]);
		close(p->p2[0]);
		close(p->p2[1]);
	}
	waitpid(id[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return(WTERMSIG(status) + 128);
	return (1);
}

void	child_process(t_cmd cmd, t_env *env, int i, t_pipe p, int her)
{
	char	**path;
	char	*temp;
	int		io[2];

	io[0] = set_in(i, cmd, her);
	io[1] = set_out(cmd);
	if (io[1] == -1)
		exit (1);
	cmd_checker(p, cmd, io, i);
	path = ft_split(find_path(env), ':');
	if (!path)
	{
		ft_dprintf("%s: No such file or directory\n", cmd.cmd[0]);
		exit(127);
	}
	if (cmd.cmd)
		temp = check_path(path, cmd.cmd);
	else
		temp = 0;
	free_strs(path);
	execve(temp, cmd.cmd, ls_to_arr(env));
}

void	multiple_cmds(int count, t_cmd *cmd, t_env **env)
{
	pid_t	id[count];
	t_pipe	p;
	int		i;
	int		cmdsize;
	int		her[count];
	t_cmd *temp;
	int	io[2];
	
	temp = cmd;
	i = 0;
	while (temp && i < count)
	{	
		her[i] = find_herdoc(temp, *env);
		if (her[i] == -1)
		{
			g_global_data.exit_status = 1;
			return;
		}
		temp = temp->next;
		i++;
	}
	i = 0;
	cmdsize = ft_cmdsize(cmd);
	pipe(p.p1);
	pipe(p.p2);
	while (cmd && i < count)
	{
		id[i] = fork();
		if (!id[i])
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);		
			if (cmd->cmd && is_builtin(cmd->cmd[0]))
			{
				io[0] = set_in(i, *cmd, her[i]);
				io[1] = set_out(*cmd);
				if (io[1] == -1)
					exit (1);
				cmd_checker(p, *cmd, io, i);
				g_global_data.exit_status = call_builtin(env, cmd);
				exit(g_global_data.exit_status);
			}
			else
				child_process(*cmd, *env, i, p, her[i]);
		}
		check_pipe(&p, i);
		i++;
		cmd = cmd->next;
	}
	g_global_data.exit_status = ft_wait(id, cmdsize - 1, &p);
	while (--i >= 0)
		waitpid(id[i], NULL, 0);
}