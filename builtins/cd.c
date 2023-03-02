/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:19:09 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/02 21:46:22 by hhattaki         ###   ########.fr       */
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
			// dprintf(2, "%p\n", ev->value);
			free (ev->value);
			ev->value = cwd;
			break ;
		}
		ev = ev->next;
	}
	ev = env;
	while (ev)
	{
		if (!ft_strcmp(ev->key, "OLDPWD"))
		{
			// dprintf(2, "%p\n", ev->value);
			free (ev->value);
			ev->value = temp;
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
	{
		
		path = get_oldpwd(cmd, env);
	}
	if (!path)
		return (1);
	r = chdir(path);
	if (r)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(cmd.cmd[1]);
		return (1);
	}
	set_pwds(env, cwd);
	return (0);
}
