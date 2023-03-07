/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:42:58 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 14:07:55 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tool(t_token **bef, t_token *wild_cards, t_token *tmp, t_token *token)
{
	(*bef)->next = wild_cards;
	*bef = tmp;
	ft_lstdelone(token);
}

t_token	*wild_cards_expansion(char **files, t_token *token
		, t_token	**bef, t_token **toks)
{
	t_token	*wild_cards;
	t_token	*next;
	t_token	*tmp;
	int		i;

	i = -1;
	wild_cards = NULL;
	next = token->next;
	while (files && files[++i])
		ft_lstadd_back(&wild_cards, ft_lstnew(ft_strdup(files[i])));
	if (wild_cards)
		tmp = ft_lstlast(wild_cards);
	if (i && bef)
	{
		ft_lstlast(wild_cards)->next = token->next;
		tool(bef, wild_cards, tmp, token);
	}
	else if (i)
	{
		ft_lstlast(wild_cards)->next = token->next;
		*toks = wild_cards;
		ft_lstdelone(token);
	}
	ft_free_all_mfs(files);
	return (next);
}

void	do_wild_card_expansion(t_token *token, t_token **toks)
{
	t_token	*tmp;

	while (token)
	{
		if (token->type == WORD && my_strchr(token->content, '*'))
		{
			token = wild_cards_expansion(wild_cards(token->content),
					token, &tmp, toks);
		}
		else
		{
			tmp = token;
			token = token->next;
		}
	}
}
