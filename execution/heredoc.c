/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:09:16 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 16:04:19 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_utils(int should_expand, t_env *env, int p, char *hold)
{
	if (should_expand)
		var_expansion(env, &hold);
	write(p, hold, ft_strlen(hold));
	write(p, "\n", 1);
	free(hold);
}

int	wait_return(pid_t *id, int p[2])
{
	close (p[1]);
	if (ft_wait(id, 0, 0))
	{
		close(p[0]);
		return (-1);
	}
	return (p[0]);
}

void	reset_signals(int p)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	close(p);
}

int	heredoc(char *del, t_env *env, int should_expand)
{
	int		p[2];
	pid_t	id;
	char	*hold;

	pipe(p);
	id = fork();
	if (!id)
	{
		reset_signals(p[0]);
		while (1)
		{
			hold = readline("> ");
			if (!hold)
				break ;
			if (!ft_strcmp(hold, del))
			{
				free (hold);
				break ;
			}
			heredoc_utils(should_expand, env, p[1], hold);
		}
		close (p[1]);
		exit (0);
	}
	return (wait_return(&id, p));
}

int	find_heredoc(t_cmd *cmd, t_env *env)
{
	int				her;
	t_redirection	*temp;

	her = 0;
	temp = cmd->in;
	while (temp)
	{
		if (temp->type == HERE_DOC)
			her = heredoc(temp->redirection, env, temp->should_expand);
		if (her == -1)
			return (her);
		temp = temp->next;
	}
	return (her);
}
