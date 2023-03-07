/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:16:41 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/06 19:39:50 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match(char *wildcard, char *name)
{
	int		start;
	int		end;
	char	**tab;
	int		i;
	int		s;

	start = 0;
	end = 0;
	i = 0;
	s = 0;
	if (wildcard[0] != '*')
		start = START;
	if (wildcard[ft_strlen(wildcard) - 1] != '*')
		end = END;
	tab = ft_split(wildcard, '*');
	if (!tab[i])
		return (1);
	while (tab[i])
	{
		if (!i && start == START)
			s = ft_strstr(name, tab[i], s, start);
		else if (!tab[i + 1])
			s = ft_strstr(name, tab[i], s, end);
		else
			s = ft_strstr(name, tab[i], s, 0);
		if (s == -1)
		{
			free_strs(tab);
			return (0);
		}
		i++;
	}
	free_strs(tab);
	return (s);
}

int	count(char	*wildcard)
{
	char			*cwd;
	DIR				*dir;
	struct dirent	*d;
	int				i;

	cwd = getcwd(0, 0);
	dir = opendir(cwd);
	i = 0;
	if (dir)
	{
		d = readdir(dir);
		while (d)
		{
			if (!ft_strcmp(wildcard, "*") && ft_strncmp(d->d_name, ".", 1))
				i++;
			else if (match(wildcard, d->d_name) && ft_strncmp(d->d_name, ".", 1))
				i++;
			d = readdir(dir);
		}
	}
	closedir(dir);
	free (cwd);
	return (i);
}

char	**wild_cards(char	*wildcard)
{
	char			*cwd;
	DIR				*dir;
	struct dirent	*d;
	char			**files;
	int				i;

	cwd = getcwd(0, 0);
	dir = opendir(cwd);
	files = ft_calloc(count(wildcard) + 1, sizeof(char *));
	i = 0;
	if (dir)
	{
		d = readdir(dir);
		while (d)
		{
			if ((!ft_strcmp(wildcard, "*") || match(wildcard, d->d_name)) && ft_strncmp(d->d_name, ".", 1))
			{
				files[i] = ft_strdup(d->d_name);
				i++;
			}
			d = readdir(dir);
		}
	}
	closedir(dir);
	free (cwd);
	return (files);
}
