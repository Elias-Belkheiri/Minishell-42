/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:45:31 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 18:35:12 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ignore_exp_here_doc(t_token *tok)
{
	while (tok)
	{
		if (ft_strlen(tok->content) == 1 && *tok->content == '$')
			tool_1(tok);
		else if (ft_strlen(tok->content) == 2 && !ft_strcmp(tok->content, "<<"))
		{
			if (tok->next && tok->next->type == SPACE)
			{
				if (tok->next->next && tok->next->next->type != PIPE
					&& tok->next->next->type != OPERATOR)
					tool_2(tok->next->next);
			}
			else if (tok->next && tok->next->type != PIPE
				&& tok->next->type != OPERATOR)
				tool_2(tok->next);
		}
		tok = tok->next;
	}
}