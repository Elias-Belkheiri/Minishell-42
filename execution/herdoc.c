/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:09:16 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 19:35:02 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc(char *del, t_env *env, int should_expand)
{
	int p[2];
	pid_t	id;
	char	*hold;

	pipe(p);
	id = fork();
	if (!id)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
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
			if (should_expand)
				var_expansion(env, &hold);
			write (p[1], hold, ft_strlen(hold));
			write(p[1] , "\n", 1);
			free (hold);
		}
		close (p[1]);
		exit (0);
	}
	close (p[1]);
	if (ft_wait(&id, 0, 0))
	{
		close(p[0]);
		return(-1);
	}
	return (p[0]);
}

int	find_herdoc(t_cmd *cmd, t_env *env)
{
	int				her;
	t_redirection	*temp;

	her = 0;
	temp = cmd->in;
	while (temp)
	{
		if (temp->type == HERE_DOC)
			her = herdoc(temp->redirection, env, temp->should_expand);
		if (her == -1)
			return (her);
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
