/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:43:04 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 14:20:16 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**to_return(DIR *dir, char *cwd, char **files)
{
	closedir(dir);
	free (cwd);
	return (files);
}

char	*my_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)(str + i));
	return (0);
}

int	check_for_ambiguous_redirect(t_token *token)
{
	int	n;

	n = ft_strlen(token->content) - 1;
	if (token->expanded)
	{
		if (ft_strchr(token->content, ' ') && token->content[n] != ' ')
		{
			ft_putendl_fd("ambiguous redirect", NULL, 2);
			g_global_data.exit_status = 1;
			return (1);
		}
	}
	return (0);
}

void	set_for_single_command(t_cmd *cmd, t_env *env)
{
	pid_t	id;

	id = fork();
	if (!id)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		single_cmd(cmd, env);
	}
	g_global_data.exit_status = ft_wait(&id, 0, 0);
}

int	ft_cmdsize(t_cmd *lst)
{
	int	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
