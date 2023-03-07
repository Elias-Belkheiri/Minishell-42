/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:19:09 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 20:51:03 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pwds(t_env *env, char	*temp)
{
	t_env	*ev;
	char	*cwd;

	ev = env;
	cwd = getcwd(0, 0);
	while (ev)
	{
		if (!ft_strcmp(ev->key, "PWD"))
		{
			free (ev->value);
			ev->value = ft_strdup(cwd);
			break ;
		}
		ev = ev->next;
	}
	free(cwd);
	ev = env;
	while (ev)
	{
		if (!ft_strcmp(ev->key, "OLDPWD"))
		{
			free (ev->value);
			ev->value = ft_strdup(temp);
			break ;
		}
		ev = ev->next;
	}
}

char	*get_home(t_cmd cmd, t_env *env)
{
	t_env	*ev;
	char	*path;

	ev = env;
	while (ev)
	{
		if (!ft_strcmp(ev->key, "HOME"))
		{
			path = ev->value;
			return (path);
		}
		ev = ev->next;
	}
	if (!ev)
		ft_dprintf("%s: HOME not set\n", cmd.cmd[0]);
	return (0);
}

char	*get_oldpwd(t_cmd cmd, t_env *env)
{
	t_env	*ev;
	char	*path;

	ev = env;
	while (ev)
	{
		if (!ft_strcmp(ev->key, "OLDPWD"))
		{
			path = ev->value;
			return (path);
		}
		ev = ev->next;
	}
	if (!ev)
		ft_dprintf("%s: OLDPWD not set\n", cmd.cmd[0]);
	return (0);
}

int	cd(t_cmd cmd, t_env *env)
{
	int		r;
	char	*path;
	char	*cwd;

	cwd = getcwd(0, 0);
	path = cmd.cmd[1];
	if (!cmd.cmd[1])
		path = get_home(cmd, env);
	else if (!ft_strcmp(cmd.cmd[1], "-"))
		path = get_oldpwd(cmd, env);
	if (!path)
	{
		free(cwd);
		return (1);
	}
	r = chdir(path);
	if (r)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(cmd.cmd[1]);
		free(cwd);
		return (1);
	}
	set_pwds(env, cwd);
	free(cwd);
	return (0);
}
