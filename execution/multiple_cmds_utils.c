/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:37:34 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 15:44:49 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipe(t_pipe *p, int i)
{
	if (i % 2)
	{
		close (p->p1[0]);
		close (p->p1[1]);
		pipe(p->p1);
	}
	if (i && !(i % 2))
	{
		close (p->p2[0]);
		close (p->p2[1]);
		pipe(p->p2);
	}
}

void	cmd_checker(t_pipe p, t_cmd cmd, int *io, int i)
{
	(void)cmd;
	if (i % 2 == 0)
		even_child(io[0], io[1], p);
	else
		odd_child(io[0], io[1], p);
}

int	check_in_files(char	*name)
{
	int	in_f;
	int	acc;

	acc = access(name, F_OK);
	in_f = open(name, O_RDONLY);
	if (acc == -1 || in_f == -1)
	{
		if (acc == -1)
			ft_dprintf("%s: No such file or directory\n", name);
		else
			ft_dprintf("%s: Permission denied\n", name);
		return (-1);
	}
	return (in_f);
}

int	set_in(int i, t_cmd cmd, int heredoc)
{
	int	in_f;

	if (i && !cmd.in && cmd.pipe)
		in_f = IS_PIPE;
	else if (cmd.in)
	{
		while (cmd.in)
		{
			if (cmd.in->type == IN)
				in_f = check_in_files(cmd.in->redirection);
			if (in_f == -1)
				return (in_f);
			if (!cmd.in->next && cmd.in->type == HERE_DOC)
				in_f = heredoc;
			cmd.in = cmd.in->next;
		}
	}
	else
		in_f = 0;
	return (in_f);
}

int	set_out(t_cmd cmd)
{
	int	out_f;

	if (cmd.next && !cmd.out && cmd.pipe)
		out_f = IS_PIPE;
	else if (cmd.out)
	{
		while (cmd.out)
		{
			if (cmd.out->type == OUT)
				out_f = open(cmd.out->redirection, O_RDWR | O_CREAT
						| O_TRUNC, 0644);
			else
				out_f = open(cmd.out->redirection, O_RDWR | O_CREAT
						| O_APPEND, 0644);
			if (out_f == -1)
			{
				ft_dprintf("%s: Permission denied\n", cmd.out->redirection);
				return (-1);
			}
			cmd.out = cmd.out->next;
		}
	}
	else
		out_f = 1;
	return (out_f);
}
