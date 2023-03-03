/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:05:18 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/02 22:52:52 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// reads from pipe 1 and write to pipe 2
void	odd_child(int i, int in, int out, t_pipe p)
{
	close(p.p1[1]);
	close(p.p2[0]);
	if (in > -1)
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
	// printf("%d, %d\n", p.p1[0], p.p2[1]);
	if (i == -1)
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
void	even_child(int i, int in, int out, t_pipe p)
{
	close(p.p2[1]);
	close(p.p1[0]);
	if (!i || in > -1)
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
	// printf("%d, %d\n", p.p2[0], p.p1[1]);
	if (i == -1)
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

	close(p->p1[0]);
	close(p->p1[1]);
	close(p->p2[0]);
	close(p->p2[1]);
	waitpid(id[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	child_process(t_cmd cmd, t_env *env, int i, t_pipe p)
{
	char	**path;
	char	*temp;
	int		io[2];

	// HANDLE MULTIPLE IN FILES
	io[0] = set_in(cmd);
	io[1] = set_out(cmd);
	cmd_checker(p, cmd, io, i);
	path = ft_split(find_path(env), ':');
	if (!path[0])
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

void	multiple_cmds(int count, t_cmd *cmd, t_env *env)
{
	pid_t	id[count];
	t_pipe	p;
	int		i;
	int cmdsize;

	i = 0;
	cmdsize = ft_cmdsize(cmd);
	pipe(p.p1);
	pipe(p.p2);
	while (cmd && i < count)
	{
		id[i] = fork();
		if (!id[i])
		{
			if (cmd->cmd && is_builtin(cmd->cmd[0]))
			{
				call_builtin(env, cmd);
				exit(0);
			}
			else
				child_process(*cmd, env, i, p);
		}
		check_pipe(&p, i);
		i++;
		cmd = cmd->next;
	}
	ft_wait(id, cmdsize - 1, &p);
	while (--i >= 0)
		waitpid(id[i], NULL, 0);
}