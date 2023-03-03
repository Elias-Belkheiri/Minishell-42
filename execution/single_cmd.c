/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 23:14:54 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/02 22:26:27 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fd(int *io)
{
	if (io[0])
	{
		dup2(io[0], 0);
		close(io[0]);
	}
	if (io[1] != 1)
	{
		dup2(io[1], 1);
		close(io[1]);
	}
}

char	*check_path(char	**path, char	**utils)
{
	int		i;
	char	*temp;
	char	*c;

	i = 0;
	if (!access(utils[0], F_OK && X_OK))
		return (ft_strdup(utils[0]));
	if (utils[0] && utils[0][0] != '.')
		c = ft_strjoin(ft_strdup("/"), utils[0]);
	else
		c = ft_strdup(utils[0]);
	while (path[i])
	{
		temp = ft_strjoin(ft_strdup(path[i]), c);
		if (!access(temp, F_OK && X_OK))
			break ;
		free (temp);
		i++;
	}
	if (!path[i])
	{
		ft_dprintf("%s: command not found\n", utils[0]);
		exit (127);
	}
	return (temp);
}

void	single_cmd(t_cmd *cmd, t_env *env)
{
	char	**path;
	char	*temp;
	int		io[2];

	io[0] = set_in(*cmd);
	if (!cmd->cmd)
		exit(0);
	io[1] = set_out(*cmd);
	path = ft_split(find_path(env), ':');
	if (!path)
	{
		ft_dprintf("%s: No such file or directory\n", cmd->cmd[0]);
		exit(127);
	}
	temp = check_path(path, cmd->cmd);
	free_strs(path);
	fd(io);
	execve(temp, cmd->cmd, ls_to_arr(env));
}