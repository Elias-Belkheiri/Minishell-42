/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:37:07 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/04 16:49:56 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handler(int a)
{
	(void)a;
	printf("LOL2\n");
	g_global_data.exit_status = 1;
}

void	sig_quit_handler(int a)
{
	(void)a;
	printf("LOL\n");
	exit(g_global_data.exit_status);
}