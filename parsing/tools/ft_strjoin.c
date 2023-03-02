/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:57:24 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/01 16:53:38 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*nw_str;
	int		i;

	if (!str1 && !str2)
		return (NULL);
	else if (!str1)
		return (ft_strdup(str2));
	else if (!str2)
		return (ft_strdup(str1));
	nw_str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!nw_str)
	{
		free(str1);
		return (NULL);
	}
	i = -1;
	while (str1[++i])
		nw_str[i] = str1[i];
	while (*str2)
		nw_str[i++] = *str2++;
	nw_str[i] = '\0';
	free(str1);
	return (nw_str);
}
