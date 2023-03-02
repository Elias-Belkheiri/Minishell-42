/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:38 by hhattaki          #+#    #+#             */
/*   Updated: 2022/10/08 17:44:49 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = str;
	while (i < n)
		s[i++] = 0;
}

void	*ft_calloc(size_t	n, size_t size)
{
	void	*tab;

	if (size && n >= SIZE_MAX / size)
		return (NULL);
	tab = malloc(n * size);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, n * size);
	return (tab);
}
