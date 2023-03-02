/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:37:04 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/01 16:54:15 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_data(t_token *tokens)
{
    while (tokens)
    {
        printf("Content: %s\n", tokens->content);
        printf("Type: %d\n", tokens->type);
        tokens = tokens->next;
    }
}

void	print_environment(t_env *tokens)
{
    while (tokens)
    {
        printf("|%s| ", tokens->key);
        printf("|%s|\n", tokens->value);
        tokens = tokens->next;
    }
}

int ft_error(t_token **tokens)
{
    ft_lstclear(tokens);
    return (0);
}

int	check_spaces(t_token *tok)
{
	while (tok && tok->type == SPACE)
		tok = tok->next;
	if (!tok)
		return (1);
	return (0);
}

int check_syntax_errors(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	if (token && token->type == PIPE)
		return (ft_putendl_fd("syntax error near unexpected token", "|", 2));
	if (token && !token->next && (token->type == OPERATOR || token->type == PIPE))
		return (ft_putendl_fd("syntax error near unexpected token", "newline", 2));
	while (token)
	{
		if ((token->type == OPERATOR || token->type == PIPE) && check_spaces(token->next))
			return (ft_putendl_fd("syntax error ", "Baby", 2));
		if (tmp)
		{
			if ((tmp->type == OPERATOR || tmp->type == PIPE) && (token->type == OPERATOR || token->type == PIPE))
				return (ft_putendl_fd("syntax error near unexpected token", token->content, 2));
		}
		tmp = token;
		token = token->next;
	}
	if (tmp && (tmp->type == OPERATOR || tmp->type == PIPE))
		return (ft_putendl_fd("syntax error near unexpected token", "newline", 2));
	return (1);
}