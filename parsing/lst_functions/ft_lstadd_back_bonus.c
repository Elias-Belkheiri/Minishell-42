/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:27:03 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/04 19:20:41 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*prv;

	prv = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (prv->next)
		prv = prv->next;
	prv->next = new;
}

void	ft_lstadd_back_2(t_env **lst, t_env *new)
{
	t_env	*prv;

	prv = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (prv->next)
		prv = prv->next;
	prv->next = new;
}

void	ft_lstadd_back_3(t_cmd **lst, t_cmd *new)
{
	t_cmd	*prv;

	prv = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (prv->next)
		prv = prv->next;
	prv->next = new;
}

void	ft_lstadd_back_4(t_redirection **lst, t_redirection *new)
{
	t_redirection	*prv;

	prv = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (prv->next)
		prv = prv->next;
	prv->next = new;
}

void	ft_lstadd_back_5(t_exp **lst, t_exp *new)
{
	t_exp	*prv;

	prv = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (prv->next)
		prv = prv->next;
	prv->next = new;
}
