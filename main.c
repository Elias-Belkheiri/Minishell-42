/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:23 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/03 15:49:23 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_token	*tokens;
	t_env	*environment;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	environment = NULL;
	g_global_data.exit_status = 0;
	if (!parse_env(envp, &environment))
		write(2, "Invalid environment\n", 21);
	while (1)
	{
		tokens = NULL;
		cmds = NULL;
		line = readline(RED "minishell$ " RESET);
		if (!line)
			exit(g_global_data.exit_status); // exit with the last exit status $? and not 0
		add_history(line);
		if (tokenize(line, &tokens))
		{
			expansion(tokens, environment, &tokens);
			del_spaces(tokens, &tokens);
			if (check_syntax_errors(tokens))
			{
				parse_cmds(&cmds, &tokens);
				check(cmds, environment);
				clear_cmds(&cmds);
			}
			else
				ft_lstclear(&tokens);
		}
		free(line);
	}
}