/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:18:26 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/06 13:22:48 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char *str1, char *str2)
{
	if (!str2)
		free (str1);
	if (str2)
		free (str2);
}

void	tool_1(t_token *tok)
{
	if (tok->next && (tok->next->type == DOUBLE || tok->next->type == SINGLE))
	{
		free(tok->content);
		tok->content = ft_strdup("");
	}
}

void	tool_2(t_token *tok)
{
	if (tok->type == WORD)
		tok->type = SINGLE_EXPAND;
	else
		tok->type = SINGLE;
}