/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:21:01 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/02 23:20:25 by hhattaki         ###   ########.fr       */
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

void	call_builtin(t_env *env_var, t_cmd	*cmd)
{
	if (!ft_strcmp("echo", cmd->cmd[0]))
		echo(cmd->cmd);
	else if (!ft_strcmp("cd", cmd->cmd[0]))
		cd(*cmd, env_var);
	else if (!ft_strcmp("unset", cmd->cmd[0]))
		unset(cmd->cmd, env_var);
	else if (!ft_strcmp("pwd", cmd->cmd[0]))
		pwd();
	else if (!ft_strcmp("env", cmd->cmd[0]))
		env(env_var);
	else if (!ft_strcmp("export", cmd->cmd[0]))
		export(env_var, cmd->cmd);	
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
			waitpid(id, 0, 0);
		}
	}
	else
		multiple_cmds(i, cmd, env);
}
