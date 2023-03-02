/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:10:03 by hhattaki          #+#    #+#             */
/*   Updated: 2023/02/28 20:34:42 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_count(t_cmd cmd)
{
	int		c;
	t_cmd	*temp;

	c = 0;
	temp = &cmd;
	while (temp)
	{
		c++;
		temp = temp->next;
	}
	return (c);
}