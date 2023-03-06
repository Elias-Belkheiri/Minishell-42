/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:37:07 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/06 11:39:11 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handler(int a)
{
	(void)a;
	// add replace line
	// write(STDOUT_FILENO,"\b",1);
	rl_on_new_line();
	rl_redisplay();
	// rl_replace_line();
	// g_global_data.exit_status = 1;
}
