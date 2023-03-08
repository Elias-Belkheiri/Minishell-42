/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:03 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 15:44:54 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_count(t_cmd cmd)
{
	int		c;
	t_cmd	*temp;

	c = 0;
	temp = &cmd;
	while (temp)
	{
		c++;
		temp = temp->next;
	}
	return (c);
}

void	file_error(int in, t_cmd cmd)
{
	if (in == -1)
		exit (1);
	if (cmd.err == 1)
		exit(1);
}

int	*open_heredocs(int count, t_cmd *cmd, t_env *env)
{
	int		*her;
	t_cmd	*temp;
	int		i;

	i = 0;
	her = malloc(count * sizeof(int));
	temp = cmd;
	while (temp && i < count)
	{	
		her[i] = find_heredoc(temp, env);
		if (her[i] == -1)
		{
			g_global_data.exit_status = 1;
			return (0);
		}
		temp = temp->next;
		i++;
	}
	return (her);
}

void	cmd_type(t_utils *utils, int i, t_cmd *cmd, t_env **env)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (cmd->cmd && is_builtin(cmd->cmd[0]))
	{
		utils->io[0] = set_in(i, *cmd, utils->her[i]);
		utils->io[1] = set_out(*cmd);
		if (utils->io[1] == -1)
			exit (1);
		cmd_checker(utils->p, *cmd, utils->io, i);
		g_global_data.exit_status = call_builtin(env, cmd);
		exit(g_global_data.exit_status);
	}
	else
		child_process(*cmd, *env, i, utils);
}

void	free_utils(int *utils, pid_t *id)
{
	free(utils);
	free(id);
}
