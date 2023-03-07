/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:00:12 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 13:32:34 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	escape_separators(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
		i++;
	if (i && *tokens)
		ft_lstadd_back(tokens, ft_lstnew(ft_strdup(" ")));
	if (is_separator(line + i) == 1)
	{
		ft_lstadd_back(tokens, ft_lstnew(ft_substr(line + i, 0, 1)));
		return (i + 1);
	}
	if (is_separator(line + i) == 2)
	{
		ft_lstadd_back(tokens, ft_lstnew(ft_substr(line + i, 0, 2)));
		return (i + 2);
	}
	return (i);
}

int	get_quotes(char *line, t_token **tokens, int quotes, int *error)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != quotes)
			i++;
	if (line[i] != quotes)
	{
		write (2, "Syntax Error baby\n", 18);
		*error = 0;
		return (0);
	}
	ft_lstadd_back(tokens, ft_lstnew(ft_substr(line, 0, i + 1)));
	return (i + 1);
}

int	get_words(char *line, t_token **tokens, int *error)
{
	int	i;

	i = 0;
	if (*line == '\'' || *line == '\"')
		return (get_quotes(line, tokens, *line, error));
	if (is_separator(line + i))
		return (0);
	while (line[i] && !is_separator(line + i)
		&& line[i] != '\'' && line[i] != '\"')
		i++;
	if (i)
		ft_lstadd_back(tokens, ft_lstnew(ft_substr(line, 0, i)));
	return (i);
}

int	tokenize(char *line, t_token **tokens)
{
	int	i;
	int	error;

	i = 0;
	error = 1;
	while (line[i])
	{
		i += escape_separators(line + i, tokens);
		i += get_words(line + i, tokens, &error);
		if (!error)
			return (ft_error(tokens));
	}
	return (1);
}
