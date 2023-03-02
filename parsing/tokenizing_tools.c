/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:29:34 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/27 22:47:26 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_mode(char *token)
{
	if (*token == '~' && ft_strlen(token) == 1)
		return (HYPHEN);
	if (*token == '\"')
		return (DOUBLE);
	if (*token == '\'')
		return (SINGLE);
	if (*token == ' ')
		return (SPACE);
	if (*token == '|')
		return (PIPE);
	if (token[0] && token[1] && !ft_strncmp(token, "<<", 2))
		return (OPERATOR);
	if (token[0] && token[1] && !ft_strncmp(token, ">>", 2))
		return (OPERATOR);
	if (*token == '<' || *token == '>')
		return (OPERATOR);
	else
		return (WORD);
}

int	is_separator(char *line)
{
	if (*line && ((*line >= 9 && *line <= 13) || *line == 32))
		return (3);
	if (*line == '|')
		return (1);
	if (!ft_strncmp(line, ">>", 2) || !ft_strncmp(line, "<<", 2))
		return (2);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}
