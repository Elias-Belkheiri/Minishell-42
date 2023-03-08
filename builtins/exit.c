/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:38:39 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 23:09:16 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check_max(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

void	num_args(char	*hold)
{
	ft_dprintf("exit: %s: numeric argument required\n", hold);
	g_global_data.exit_status = 255;
	exit (g_global_data.exit_status);
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	n;
	char	*hold;

	sign = 1;
	n = 0;
	hold = (char *)str;
	while (str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (str && !*str)
		num_args(hold);
	if (str && (*str == '+' || *str == '-'))
		if (*str++ == '-')
			sign *= -1;
	while (str && (*str >= '0' && *str <= '9'))
	{
		n = n * 10 + *str++ - '0';
		if (n > 9223372036854775807)
			return (check_max(sign));
	}
	if (str && *str && (*str < '0' || *str > '9'))
		num_args(hold);
	return (n * sign);
}

int	ft_exit(char **arg)
{
	int	n;

	if (!arg[1])
	{
		printf("exit\n");
		exit (g_global_data.exit_status);
	}
	ft_atoi(ft_strdup(arg[1]));
	if (arg[2])
	{
		ft_dprintf("exit\nexit: too many argument\n", 0);
		return (1);
	}
	printf("exit\n");
	n = (unsigned char)ft_atoi(arg[1]);
	exit(n);
	return (0);
}
