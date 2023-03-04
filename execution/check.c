/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:21:01 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/04 00:42:13 by hhattaki         ###   ########.fr       */
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

int	call_builtin(t_env *env_var, t_cmd	*cmd)
{
	int	ex;

	ex = 0;
	if (!ft_strcmp("echo", cmd->cmd[0]))
		ex = echo(cmd->cmd);
	else if (!ft_strcmp("cd", cmd->cmd[0]))
		ex = cd(*cmd, env_var);
	else if (!ft_strcmp("unset", cmd->cmd[0]))
		ex = unset(cmd->cmd, env_var);
	else if (!ft_strcmp("pwd", cmd->cmd[0]))
		ex = pwd();
	else if (!ft_strcmp("env", cmd->cmd[0]))
		ex = env(env_var);
	else if (!ft_strcmp("export", cmd->cmd[0]))
		ex = export(env_var, cmd->cmd);
		else if (!ft_strcmp("exit", cmd->cmd[0]))
		ex = ft_exit(cmd->cmd);
	return (ex);
}

void	check(t_cmd *cmd, t_env *env)
{
	int		i;
	pid_t	id;

	i = 0;
	// while (cmd->cmd[i])
	// {
	// 	printf("%s", cmd->cmd[i]);
	// 	i++;
	// }
	i = ft_cmdsize(cmd);
	if (!cmd->next)
	{
		// printf("here%s\n", cmd->cmd[1]);
		if (cmd->cmd && cmd->cmd[0] && is_builtin(cmd->cmd[0]))
			call_builtin(env, cmd);
		else
		{
			// cmd->cmd[0] = join("/", cmd->cmd[0]);
			id = fork();
			if (!id)
				single_cmd(cmd, env);
			waitpid(id, &(g_global_data.exit_status), 0);
			if (WIFEXITED(g_global_data.exit_status))
				g_global_data.exit_status = WEXITSTATUS(g_global_data.exit_status);
		}
	}
	else
		multiple_cmds(i, cmd, env);
}
