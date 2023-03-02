/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:03:29 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/01 16:53:13 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_putnb(long nb, char *p, int *i)
{
	int	idx;

	idx = *i;
	if (nb < 0)
	{
		p[idx] = '-';
		nb *= -1;
		idx++;
		*i = idx;
	}
	if (nb <= 9)
	{
		p[idx] = nb + '0';
		idx++;
		*i = idx;
	}
	else if (nb > 9)
	{
		ft_putnb(nb / 10, p, i);
		ft_putnb(nb % 10, p, i);
	}
}

char	*ft_itoa(int n)
{
	int		num;
	int		i;
	int		sign;
	char	*p;

	num = n;
	i = 0;
	sign = 0;
	if (n < 0 || !n)
		sign = 1;
	while (num)
	{
		num /= 10;
		i++;
	}
	p = malloc(i + sign + 1);
	if (!p)
		return (NULL);
	i = 0;
	ft_putnb(n, p, &i);
	p[i] = '\0';
	return (p);
}
