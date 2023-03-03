/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:37:34 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/03 16:39:09 by hhattaki         ###   ########.fr       */
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

// void	cmd_checker(t_pipe p, int *io, int i)
// {
// 	if (i % 2 == 0)
// 		even_child(io[0], io[1], p);
// 	else
// 		odd_child(io[0], io[1], p);
// }

int	set_in(int i, t_cmd cmd)
{
	int	in_f;

	if (i && cmd.next && !cmd.in && cmd.pipe)
		in_f = IS_PIPE;
	else if (cmd.in)
	{
		while (cmd.in)
		{
			if (cmd.in->type == IN)
			{
				in_f = open(cmd.in->redirection, O_RDONLY);
				if (in_f == -1)
				{
					ft_dprintf("%s: No such file or directory\n", cmd.in->redirection);
					exit (1);	
				}
			}
			else
				in_f = herdoc(cmd.in->redirection);
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
				out_f = open(cmd.out->redirection, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				out_f = open(cmd.out->redirection, O_RDWR | O_CREAT | O_APPEND, 0644);
			cmd.out = cmd.out->next;
		}
	}
	else
		out_f = 1;
	return (out_f);
}
