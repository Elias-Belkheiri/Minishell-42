/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:37:07 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 19:42:38 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handler(int a)
{
	(void)a;
	write(1,"\n",1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
