/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:27:14 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 12:18:04 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*ptr;
	t_token	*tmp;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		ft_lstdelone(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}

void	ft_lstclear_2(t_redirection **lst)
{
	t_redirection	*ptr;
	t_redirection	*tmp;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->redirection);
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}
