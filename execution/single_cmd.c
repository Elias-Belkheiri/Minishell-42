/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 23:14:54 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 02:27:10 by hhattaki         ###   ########.fr       */
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
	if (ft_strcmp(utils[0], ".") && my_strchr(utils[0], '/'))
	{
		if (!access(utils[0], F_OK) && !access(utils[0], X_OK))
			return (ft_strdup(utils[0]));
		else if (!access(utils[0], F_OK))
		{
			ft_dprintf("%s: Permission denied\n", utils[0]);
			exit(126);
		}
	}
	if (utils[0] && utils[0][0] != '.')
		c = ft_strjoin(ft_strdup("/"), utils[0]);
	else
		c = ft_strdup(utils[0]);
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
		closedir(dir);
		exit(g_global_data.exit_status);
	}
}

int	check_for_ambiguous_redirect(t_token *token)
{
	int	n;

	n = ft_strlen(token->content) - 1;
	if (token->expanded)
	{
		if (ft_strchr(token->content, ' ') && token->content[n] != ' ')
		{
			ft_putendl_fd("ambiguous redirect", NULL, 2);
			g_global_data.exit_status = 1;
			return (1);
		}
	}
	return (0);
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
	file_error(io[0], *cmd);
	io[1] = set_out(*cmd);
	if (io[1] == -1)
		exit (1);
	if (!cmd->cmd[0])
		exit(0);
	path = ft_split(find_path(env), ':');
	if (!path && !my_strchr(cmd->cmd[0], '/'))
	{
		ft_dprintf("%s: No such file or directory\n", cmd->cmd[0]);
		exit(127);
	}
	temp = check_path(path, cmd->cmd);
	free_strs(path);
	fd(io);
	execve(temp, cmd->cmd, ls_to_arr(env));
}
