/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:59:21 by hhattaki          #+#    #+#             */
/*   Updated: 2023/02/27 21:59:46 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **key, t_env	*env_vars)
{
	t_env	*temp;
	t_env	*hold;
	int		i;

	i = 1;
	hold = env_vars;
	while (key[i])
	{
		while (env_vars)
		{
			if (!ft_strncmp(env_vars->next->key, key[i], 0))
			{
				temp = env_vars->next;
				env_vars->next = temp->next;
				free_env(temp);
				break ;
			}
			env_vars = env_vars->next;
		}
		env_vars = hold;
		i++;
	}
}