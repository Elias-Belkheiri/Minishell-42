/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:35:45 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/07 13:29:58 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_error(t_token **tokens)
{
	ft_lstclear(tokens);
	return (0);
}

void	set_operator(t_token *token, t_redirection **redirection, int type)
{
	if (token)
		ft_lstadd_back_4(redirection,
			ft_lstnew_4(ft_strdup(token->content), type));
	if (token && type == HERE_DOC && token->type == SINGLE_EXPAND)
		ft_lstlast_3(*redirection)->should_expand = 1;
}

void	is_operator(t_token *token, t_cmd *cmd)
{
	if (token->next)
	{
		if (check_for_ambiguous_redirect(token->next))
		{
			cmd->err = 1;
			return ;
		}
	}
	if (!ft_strcmp(token->content, "<<"))
		set_operator(token->next, &cmd->in, HERE_DOC);
	else if (*(token->content) == '<')
		set_operator(token->next, &cmd->in, IN);
	else if (!ft_strcmp(token->content, ">>"))
		set_operator(token->next, &cmd->out, APPEND);
	else if (*(token->content) == '>')
		set_operator(token->next, &cmd->out, OUT);
}

void	hyphen_expansion(t_token *token, t_env *env)
{
	char	*tmp;

	if (token)
	{
		tmp = token->content;
		token->content = get_expansion(env, ft_strdup("HOME"));
		free(tmp);
	}
}

void	initialize_args(t_token *token, t_cmd *command)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOUBLE
			|| token->type == SINGLE || token->type == HYPHEN)
			i++;
		token = token->next;
	}
	if (!i++)
		return ;
	command->cmd = malloc(i * sizeof(char *));
	if (!command->cmd)
		return ;
	command->cmd[--i] = NULL;
}
