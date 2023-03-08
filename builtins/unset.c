/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:59:21 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 23:58:28 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *key)
{
	ft_dprintf("unset: `%s': not a valid identifier\n", key);
	return (1);
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
			ex = print_error(key[i]);
		temp = 0;
		while (r == -1 && hold)
		{
			if (hold && !ft_strcmp(hold->key, key[i]))
			{
				ft_lstdel_2(temp, hold, env_vars);
				break ;
			}
			temp = hold;
			hold = hold->next;
		}
		hold = *env_vars;
		i++;
	}
	return (ex);
}
