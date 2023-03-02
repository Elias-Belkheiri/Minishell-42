/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:07:59 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/01 16:53:16 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_putendl_fd(char *s, char *str, int fd)
{
	if (!s)
	{
		write (fd, "\n", 1);
		return (0);
	}
	if (*str == '/')
		str++;
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
	if (str)
	{
		write(fd, "`", 1);
		while (*str)
		{
			write (fd, str, 1);
			str++;
		}
		write(fd, "\'", 1);
	}
	write (fd, "\n", 1);
	g_global_data.exit_status = 258;
	return (0);
}
