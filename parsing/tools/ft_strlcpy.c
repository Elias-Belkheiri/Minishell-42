/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:55:59 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/01 16:53:41 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)src;
	if (!dstsize)
		return (ft_strlen(s));
	if (dstsize <= 0)
		dstsize = ft_strlen(s) + 1;
	while (dstsize-- > 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(s));
}
