/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:54:49 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 15:57:40 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstdel(t_token *bef, t_token **current, t_token **tokens)
{
	t_token	*tmp;

	if (!bef)
	{
		*tokens = (*current)->next;
		ft_lstdelone(*current);
		(*current) = NULL;
	}
	else
	{
		tmp = (*current)->next;
		ft_lstdelone(*current);
		bef->next = tmp;
		*current = tmp;
	}
}

void	ft_lstdel_2(t_env *bef, t_env *current, t_env **tokens)
{
	t_env	*tmp;

	if (!bef)
	{
		*tokens = current->next;
		free_env(current);
		current = NULL;
	}
	else
	{
		tmp = current->next;
		free_env(current);
		bef->next = tmp;
		current = tmp;
	}
}
