/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:16:41 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 13:32:01 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_int
{
	int	s;
	int	start;
	int	end;
}	t_int;

void	init_ints(t_int	*utils, char *wildcard)
{
	utils->start = 0;
	utils->end = 0;
	utils->s = 0;
	if (wildcard[0] != '*')
		utils->start = START;
	if (wildcard[ft_strlen(wildcard) - 1] != '*')
		utils->end = END;
}

void	check_file_name(int i, char **tab, t_int *utils, char *name)
{
	if (!i && utils->start == START)
		utils->s = ft_strstr(name, tab[i], utils->s, utils->start);
	else if (!tab[i + 1])
		utils->s = ft_strstr(name, tab[i], utils->s, utils->end);
	else
		utils->s = ft_strstr(name, tab[i], utils->s, 0);
}

int	match(char *wildcard, char *name)
{
	char	**tab;
	int		i;
	t_int	utils;

	i = 0;
	init_ints(&utils, wildcard);
	tab = ft_split(wildcard, '*');
	if (!tab[i])
	{
		free_strs(tab);
		return (1);
	}
	while (tab[i])
	{
		check_file_name(i, tab, &utils, name);
		if (utils.s == -1)
		{
			free_strs(tab);
			return (0);
		}
		i++;
	}
	free_strs(tab);
	return (utils.s);
}

int	count(char	*str)
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
			if (!ft_strcmp(str, "*") && ft_strncmp(d->d_name, ".", 1))
				i++;
			else if (match(str, d->d_name) && ft_strncmp(d->d_name, ".", 1))
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
			if ((!ft_strcmp(wildcard, "*") || match(wildcard, d->d_name))
				&& ft_strncmp(d->d_name, ".", 1))
			{
				files[i] = ft_strdup(d->d_name);
				i++;
			}
			d = readdir(dir);
		}
	}
	return (to_return(dir, cwd, files));
}
