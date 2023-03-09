/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:23 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/09 12:41:25 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals(int argc, char **argv, t_env **environment, char **envp)
{
	(void)argc;
	(void)argv;
	*environment = NULL;
	g_global_data.exit_status = 0;
	parse_env(envp, environment);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
}

void	meh(t_token **tokens, t_env **environment, t_cmd **cmds)
{
	expansion(*tokens, *environment, tokens);
	del_spaces(*tokens, tokens);
	do_wild_card_expansion(*tokens, tokens);
	if (check_syntax_errors(*tokens))
	{
		parse_cmds(cmds, tokens);
		check(*cmds, environment);
		clear_cmds(cmds);
	}
	else
		ft_lstclear(tokens);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_token	*tokens;
	t_env	*environment;
	t_cmd	*cmds;

	set_signals(argc, argv, &environment, envp);
	while (1)
	{
		tokens = NULL;
		cmds = NULL;
		line = readline(RED "Minishell$ " RESET);
		if (!line)
			exit(g_global_data.exit_status);
		add_history(line);
		if (tokenize(line, &tokens))
			meh(&tokens, &environment, &cmds);
		free(line);
	}
}
