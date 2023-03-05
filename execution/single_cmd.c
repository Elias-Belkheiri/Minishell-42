/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 23:14:54 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/05 18:17:51 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)(str + i));
	return (0);
}

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
	if (!utils)
		return (0);	
	if (ft_strcmp(utils[0], ".") && my_strchr(utils[0], '/') && !access(utils[0], F_OK))
	{
		if (!access(utils[0], X_OK))
			return (ft_strdup(utils[0]));
		else
		{
			ft_dprintf("%s: Permission denied\n", utils[0]);
			exit(126);
		}
	}
	if (utils[0] && utils[0][0] != '.')
		c = ft_strjoin(ft_strdup("/"), utils[0]);
	else
	{
		c = ft_strdup(utils[0]);
	}
	while (path[i] && ft_strcmp(utils[0], "."))
	{
		temp = ft_strjoin(ft_strdup(path[i]), c);
		if (!access(temp, F_OK && X_OK))
			break ;
		free (temp);
		i++;
	}
	if (!path[i] || !ft_strlen(utils[0]) || !ft_strcmp(utils[0], "."))
	{
		ft_dprintf("%s: command not found\n", utils[0]);
		exit (127);
	}
	return (temp);
}

void	check_if_dir(char	*name)
{
	DIR		*dir;
	
	dir = opendir(name);
	if (dir)
	{
		ft_dprintf("%s: is a directory\n", name);
		g_global_data.exit_status = 126;
		exit(g_global_data.exit_status);
	}
}

int	check_for_ambiguous_redirect(t_redirection *redir)
{
	int	n;

	while (redir)
	{
		n = ft_strlen(redir->redirection) - 1;
		if (ft_strchr(redir->redirection, ' ') && redir->redirection[n] != ' ')
			return (0);
		redir = redir->next;
	}
	return(1);
}

void	single_cmd(t_cmd *cmd, t_env *env)
{
	char	**path;
	char	*temp;
	int		io[2];
	int		her;

	if (cmd->cmd && my_strchr(cmd->cmd[0], '/'))
		check_if_dir(cmd->cmd[0]);
	her = find_herdoc(cmd, env);
	io[0] = set_in(0, *cmd, her);
	if (!cmd->cmd)
		exit(0);
	io[1] = set_out(*cmd);
	if (io[1] == -1)
		exit (1);
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