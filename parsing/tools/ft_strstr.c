/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:17:22 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 15:14:48 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_end(char *big, char *lil)
{
	int	l_b;
	int	l_l;

	l_b = ft_strlen(big) - 1;
	l_l = ft_strlen(lil) - 1;
	while (l_l >= 0 && l_b >= 0)
	{
		if (lil[l_l] != big[l_b])
			break ;
		l_l--;
		l_b--;
	}
	if (l_l < 0)
		return (1);
	return (-1);
}

int	check_start(char *big, char *lil, int start)
{
	while (big[start] && lil[start])
	{
		if (lil[start] && lil[start] != big[start])
			break ;
		start++;
	}
	if (!lil[start])
		return (start);
	return (-1);
}

int	ft_strstr(char *big, char *lil, int start, int pos)
{
	int		j;

	if (pos == START)
		return (check_start(big, lil, start));
	if (pos == END)
		return (check_end(big, lil));
	while (big[start])
	{
		j = 0;
		while (big[start + j] && big[start + j] == lil[j])
			j++;
		if (!lil[j])
			return (start + j);
		start++;
	}
	return (-1);
}
