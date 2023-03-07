/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:16:40 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 21:37:10 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	to_print(char	**av, int i)
{
	int	j;
	int	t;

	j = i;
	if (!av)
		return ;
	while (av && av[i] && av[i + 1])
	{
		t = 0;
		while (av[i][t] && av[i][0] == '-')
		{
			t++;
			if (av[i][t] != 'n')
				break ;
		}
		if (av[i][t])
			printf("%s ", av[i]);
		i++;
	}
	if (j == 2)
		printf("%s", av[i]);
	else if (j == 1)
		printf("%s\n", av[i]);
}

int	echo(char **av)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	if (!av[1])
	{
		printf("\n");
		return (0);
	}
	while (av[1] && av[1][0] && av[1][i] && av[1][0] == '-')
	{
		i++;
		if (av[1][i] != 'n')
		{
			s = 1;
			break ;
		}
	}
	if (av[1] && s && !av[1][i])
		to_print(av, 2);
	else if (av[1])
		to_print(av, 1);
	return (0);
}
