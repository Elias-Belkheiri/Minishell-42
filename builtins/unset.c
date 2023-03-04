/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:59:21 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/03 23:27:01 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(char **key, t_env	*env_vars)
{
	t_env	*temp;
	t_env	*hold;
	int		i;
	int		r;
	int		ex;

	i = 1;
	ex = 0;
	hold = env_vars;
	while (key[i])
	{
		r = is_alphanum(key[i]);
		if (r != -1)
		{
			ft_dprintf("unset: `%s': not a valid identifier\n", key[i]);
			ex = 1;
		}
		while (r == -1 && env_vars)
		{
			if (!ft_strcmp(env_vars->next->key, key[i]))
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
	return (ex);
}