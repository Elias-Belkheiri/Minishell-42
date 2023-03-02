/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:31:56 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/02 19:02:51 by hhattaki         ###   ########.fr       */
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

void	print_cmd(t_cmd *command)
{
	int	i;

	i = 0;
	while (command)
	{
		printf("------------\n");
		i = -1;
		while (command->cmd && command->cmd[++i])
		{
			if (!i)
				printf("command: %s\n", command->cmd[i]);
			else
				printf("Arg: %s\n", command->cmd[i]);
		}
		i = 0;
		while (command->out)
		{
			if (command->out->type == OUT)
				printf("Out %d: %s\n", i++, command->out->redirection);
			else
				printf("Append %d: %s\n", i++, command->out->redirection);
			command->out = command->out->next;
		}
		while (command->in)
		{
			if (command->in->type == IN)
				printf("IN %d: %s\n", i++, command->in->redirection);
			else
				printf("HERE_DOC %d: %s\n", i++, command->in->redirection);
			command->in = command->in->next;
		}
		printf("Pipe: %d\n", command->pipe);
		command = command->next;
		printf("------------\n");
	}
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