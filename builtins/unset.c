/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:59:21 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 16:54:29 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del(char *key, t_env **hold, t_env *temp, t_env **env_vars)
{
	while (*hold)
	{
		if (hold && !ft_strcmp((*hold)->key, key))
		{
			ft_lstdel_2(temp, *hold, env_vars);
			break ;
		}
		temp = *hold;
		*hold = (*hold)->next;
	}		
}

int	unset(char **key, t_env	**env_vars)
{
	t_env	*temp;
	t_env	*hold;
	int		i;
	int		r;
	int		ex;

	i = 1;
	ex = 0;
	hold = *env_vars;
	while (key[i])
	{
		r = is_alphanum(key[i]);
		if (r != -1)
		{
			ft_dprintf("unset: `%s': not a valid identifier\n", key[i]);
			ex = 1;
		}
		temp = 0;
		if (r == -1)
			del(key[i], &hold, temp, env_vars);
		hold = *env_vars;
		i++;
	}
	return (ex);
}
