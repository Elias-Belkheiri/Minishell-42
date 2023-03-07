/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:18:26 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 18:38:06 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char *str1, char *str2, char *content, char *expansion)
{
	if (!str2)
		free (str1);
	if (str2)
		free (str2);
	free(content);
	free(expansion);
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

int	check_digits(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (1);
	while (str[i] && !is_expansion_separator(str[i]))
		i++;
	return (i);
}

int	must_expand(int a, int b)
{
	if (a == '$' && b == '?')
		return (1);
	if (a == '$' && !is_expansion_separator(b))
		return (1);
	return (0);
}