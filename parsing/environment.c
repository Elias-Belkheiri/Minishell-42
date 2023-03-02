/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:42:44 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/27 22:40:16 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_keys_values(char	*envp, t_env	**environment)
{
	int	idx;

	idx = ft_strchr(envp, '=');
	ft_lstadd_back_2(environment, ft_lstnew_2(ft_substr(envp, 0, idx),
			ft_substr(envp, idx + 1, ft_strlen(envp) - idx)));
}

void	*parse_env(char **envp, t_env **environment)
{
	if (!envp || !*envp)
		return (NULL);
	while (*envp)
	{
		get_keys_values(*envp, environment);
		envp++;
	}
	return (envp);
}
