/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:31:56 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 14:02:55 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialize_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->pipe = 0;
}

int	is_expansion_separator(int a)
{
	if (!ft_isalnum(a) && a != '_')
		return (1);
	return (0);
}

void	ft_free_all_mfs(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	clear_cmds(t_cmd **cmds)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	if (!cmds || !*cmds)
		return ;
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->in)
			ft_lstclear_2(&tmp->in);
		if (tmp->out)
			ft_lstclear_2(&tmp->out);
		if (tmp->cmd)
			ft_free_all_mfs(tmp->cmd);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

int	ft_join(t_token **token, t_token *bef)
{
	if ((*token)->type == SPACE
		|| (*token)->type == PIPE || (*token)->type == OPERATOR)
		return (0);
	if (!bef || bef->type == SPACE
		|| bef->type == PIPE || bef->type == OPERATOR)
		return (0);
	else
	{
		bef->content = ft_strjoin(bef->content, (*token)->content);
		bef->next = (*token)->next;
		ft_lstdelone(*token);
		*token = bef->next;
		return (1);
	}
}
