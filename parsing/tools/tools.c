/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:37:04 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/09 13:36:29 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_spaces(t_token *tok)
{
	while (tok && tok->type == SPACES)
		tok = tok->next;
	if (!tok)
		return (1);
	return (0);
}

int	syntax_error_tool(t_token *token, t_token *tmp, int a)
{
	if (a)
	{
		if (tmp->type == OPERATOR && token->type == PIPE)
			return (ft_putendl_fd("syntax error near unexpected token"
					, token->content, 2));
		if (tmp->type == OPERATOR && token->type == OPERATOR)
			return (ft_putendl_fd("syntax error near unexpected token"
					, token->content, 2));
		if (tmp->type == PIPE && token->type == PIPE)
			return (ft_putendl_fd("syntax error near unexpected token"
					, token->content, 2));
		if (tmp->type == PIPE && token->type == OPERATOR
			&& (!token->next || token->next->type == OPERATOR
				|| token->next->type == PIPE))
			return (ft_putendl_fd("syntax error near unexpected token"
					, token->content, 2));
	}
	return (1);
}

int	syntax_error_tool_2(t_token *token)
{
	if (token && token->type == PIPE)
		return (ft_putendl_fd("syntax error near unexpected token", "|", 2));
	if (token && !token->next && (token->type == OPERATOR
			|| token->type == PIPE))
		return (ft_putendl_fd("syntax error near unexpected token"
				, "newline", 2));
	return (1);
}

int	syntax_error_tool_3(t_token *token, t_token *tmp)
{
	if ((tmp->type == OPERATOR || tmp->type == PIPE)
		&& (token->type == OPERATOR || token->type == PIPE))
	{
		if (!syntax_error_tool(token, tmp, 1))
			return (0);
	}
	return (1);
}

int	check_syntax_errors(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	if (token && token->type == PIPE)
		return (ft_putendl_fd("syntax error near unexpected token"
				, "|", 2));
	if (token && !token->next && (token->type == OPERATOR
			|| token->type == PIPE))
		return (ft_putendl_fd("syntax error near unexpected token"
				, "newline", 2));
	while (token)
	{
		if ((!ft_strcmp(token->content, "&&")
				|| !ft_strcmp(token->content, "&"))
			&& token->type == WORD)
			return (ft_putendl_fd("syntax error Baby", NULL, 2));
		if (tmp && !syntax_error_tool_3(token, tmp))
			return (0);
		tmp = token;
		token = token->next;
	}
	if (tmp && (tmp->type == OPERATOR || tmp->type == PIPE))
		return (ft_putendl_fd("syntax error near unexpected token"
				, "newline", 2));
	return (1);
}
