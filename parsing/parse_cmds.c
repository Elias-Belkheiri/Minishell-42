/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:36:22 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/03 15:33:30 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_cmd(t_cmd *cmd, t_token *token, int *i)
{
	if (!token || token->type == SPACE)
		return ;
	if ((token->type == WORD || token->type == DOUBLE
			|| token->type == SINGLE || token->type == HYPHEN) && cmd->cmd)
		cmd->cmd[(*i)++] = ft_strdup(token->content);
	else if (*(token->content) == '|')
	{
		if (token->next && token->next->content)
			cmd->pipe = 1;
	}
}

void	del_spaces(t_token *token, t_token **tokens)
{
	t_token	*bef;

	bef = NULL;
	while (token)
	{
		if (token->type == SPACE)
			ft_lstdel(bef, &token, tokens);
		else
		{
			bef = token;
			token = token->next;
		}
	}
}

void	erase_operators(t_cmd *cmd, t_token *token, t_token **toks)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == OPERATOR)
		{
			is_operator(token, ft_lstlast2(cmd));
			if (token && token->next)
			{
				tmp2 = token->next->next;
				ft_lstdel(token, &token->next, toks);
				ft_lstdel(tmp, &token, toks);
				token = tmp2;
			}
		}
		else
		{
			tmp = token;
			token = token->next;
		}
	}
}

void	parse_initialization(t_cmd **cmds, t_token **toks)
{
	ft_lstadd_back_3(cmds, ft_lstnew_3());
	initialize_cmd(ft_lstlast2(*cmds));
	erase_operators(*cmds, *toks, toks);
	initialize_args(*toks, ft_lstlast2(*cmds));
}

int	parse_cmds(t_cmd **cmds, t_token **toks)
{
	t_token			*tok;
	t_token			*token;
	int				i;
	static int		pipe;

	i = 0;
	parse_initialization(cmds, toks);
	if (pipe && !ft_lstlast2(*cmds)->in)
		ft_lstlast2(*cmds)->pipe = pipe--;
	token = *toks;
	while (token && token->type != PIPE)
	{
		tok = token;
		fill_cmd(ft_lstlast2(*cmds), token, &i);
		token = token->next;
		ft_lstdelone(tok);
	}
	if (!token)
		return (0);
	*toks = token->next;
	fill_cmd(ft_lstlast2(*cmds), token, &i);
	ft_lstdelone(token);
	if (ft_lstlast2(*cmds)->pipe)
		pipe++;
	return (parse_cmds(cmds, toks));
}