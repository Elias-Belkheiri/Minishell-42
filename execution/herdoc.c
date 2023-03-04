/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:09:16 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/04 16:24:39 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc(char *del)
{
	int p[2];
	pid_t	id;
	char	*hold;

	pipe(p);
	id = fork();
	if (!id)
	{
		close(p[0]);
		while (1)
		{
			hold = readline("> ");
			if (!hold)
				break ;
			if (!ft_strcmp(hold, del))
			{
				free (hold);
				break;
			}
			write (p[1], hold, ft_strlen(hold));
			write(p[1] , "\n", 1);
			free (hold);
		}
		close (p[1]);
		exit (0);
	}
	waitpid(id, 0, 0);
	close (p[1]);
	// dprintf(2, "to ret %d\n", p[0]);
	return (p[0]);
}

int	find_herdoc(t_cmd *cmd)
{
	int				her;
	// t_cmd			*temp;
	t_redirection	*temp;

	her = 0;
	temp = cmd->in;
	while (temp)
	{
		if (temp->type == HERE_DOC)
			her = herdoc(temp->redirection);
		temp = temp->next;
	}
	return (her);
}

int	ft_cmdsize(t_cmd *lst)
{
	int	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
