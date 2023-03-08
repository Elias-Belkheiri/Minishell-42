/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:05:18 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 15:44:31 by hhattaki         ###   ########.fr       */
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
		return (WTERMSIG(status) + 128);
	return (1);
}

void	child_process(t_cmd cmd, t_env *env, int i, t_utils *utils)
{
	char	**path;
	char	*temp;
	int		io[2];

	if (cmd.cmd && my_strchr(cmd.cmd[0], '/'))
		check_if_dir(cmd.cmd[0]);
	io[0] = set_in(i, cmd, utils->her[i]);
	file_error(io[0], cmd);
	io[1] = set_out(cmd);
	if (io[1] == -1)
		exit (1);
	if (!cmd.cmd[0])
		exit (0);
	cmd_checker(utils->p, cmd, io, i);
	path = ft_split(find_path(env), ':');
	if (!path && !my_strchr(cmd.cmd[0], '/'))
	{
		ft_dprintf("%s: No such file or directory\n", cmd.cmd[0]);
		exit(127);
	}
	temp = 0;
	if (cmd.cmd)
		temp = check_path(path, cmd.cmd);
	free_strs(path);
	execve(temp, cmd.cmd, ls_to_arr(env));
}

void	multiple_cmds(int count, t_cmd *cmd, t_env **env)
{
	pid_t	*id;
	t_utils	utils;
	int		i;

	id = (pid_t *)malloc(count * sizeof(pid_t));
	utils.her = open_heredocs(count, cmd, *env);
	if (!utils.her)
		return ;
	i = 0;
	utils.size = ft_cmdsize(cmd);
	pipe(utils.p.p1);
	pipe(utils.p.p2);
	while (cmd && i < count)
	{
		id[i] = fork();
		if (!id[i])
			cmd_type(&utils, i, cmd, env);
		check_pipe(&(utils.p), i);
		i++;
		cmd = cmd->next;
	}
	g_global_data.exit_status = ft_wait(id, utils.size - 1, &(utils.p));
	while (--i >= 0)
		waitpid(id[i], NULL, 0);
	free_utils(utils.her, id);
}
