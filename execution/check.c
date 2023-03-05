/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:21:01 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/05 13:01:41 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join(char *str1, char *str2)
{
	char	*nw_str;
	int		i;

	if (!str1 && !str2)
		return (NULL);
	else if (!str1)
		return (ft_strdup(str2));
	else if (!str2)
		return (ft_strdup(str1));
	nw_str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!nw_str)
	{
		free(str1);
		return (NULL);
	}
	i = -1;
	while (str1[++i])
		nw_str[i] = str1[i];
	while (*str2)
		nw_str[i++] = *str2++;
	nw_str[i] = '\0';
	return (nw_str);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp("echo", cmd))
		return (1);
	if (!ft_strcmp("cd", cmd))
		return (1);
	if (!ft_strcmp("exit", cmd))
		return (1);
	if (!ft_strcmp("unset", cmd))
		return (1);
	if (!ft_strcmp("env", cmd))
		return (1);
	if (!ft_strcmp("pwd", cmd))
		return (1);
	if (!ft_strcmp("export", cmd))
		return (1);
	return (0);
}

int	call_builtin(t_env **env_var, t_cmd	*cmd)
{
	int	ex;

	ex = 0;
	if (!ft_strcmp("echo", cmd->cmd[0]))
		ex = echo(cmd->cmd);
	else if (!ft_strcmp("cd", cmd->cmd[0]))
		ex = cd(*cmd, *env_var);
	else if (!ft_strcmp("unset", cmd->cmd[0]))
		ex = unset(cmd->cmd, env_var);
	else if (!ft_strcmp("pwd", cmd->cmd[0]))
		ex = pwd();
	else if (!ft_strcmp("env", cmd->cmd[0]))
		ex = env(*env_var);
	else if (!ft_strcmp("export", cmd->cmd[0]))
		ex = export(env_var, cmd->cmd);
		else if (!ft_strcmp("exit", cmd->cmd[0]))
		ex = ft_exit(cmd->cmd);
	return (ex);
}

// If The redirections are tailed withe spaces, they must be deleted except the last one.
// << l
// << "$USER" cat | cat
void	check(t_cmd *cmd, t_env **env)
{
	int		i;
	pid_t	id;

	i = 0;
	i = ft_cmdsize(cmd);
	if (!cmd->next)
	{
		if (!check_for_ambiguous_redirect(cmd->in) || !check_for_ambiguous_redirect(cmd->out))
		{
			ft_putendl_fd("ambiguous redirect", NULL, 2);
			return ;
		}
		if (cmd->cmd && cmd->cmd[0] && is_builtin(cmd->cmd[0]))
			call_builtin(env, cmd);
		else
		{
			id = fork();
			if (!id)
			{
				signal(SIGQUIT, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				single_cmd(cmd, *env);
			}
			g_global_data.exit_status = ft_wait(&id, 0, 0);
		}
	}
	else
		multiple_cmds(i, cmd, env);
}
