/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:45:55 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 22:35:58 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new(t_env **env, int r, char *add, t_env *new)
{
	t_env	*temp;

	temp = *env;
	while (temp && temp->next)
		temp = temp->next;
	if (temp)
		temp->next = new;
	else if (!(*env))
		*env = new;
	new->key = ft_substr(add, 0, r);
	new->value = ft_substr(add, r + 2, ft_strlen(add) - r);
}

int	add_node(t_exp *temp, t_exp *bfr, char *hold, int mode)
{
	if (mode)
	{
		bfr->next = temp->next;
		free(temp->key);
		free(temp);
		free(hold);
		return (1);
	}
	else
	{
		g_global_data.exported_vars = temp;
		free(bfr->key);
		free(bfr);
		free(hold);
		return (1);		
	}
}

int	check_if_exported(char *add, int r)
{
	t_exp	*temp;
	t_exp	*bfr;
	char	*hold;
	int		i;

	bfr = g_global_data.exported_vars;
	hold = ft_substr(add, 0, r);
	i = 0;
	while (bfr)
	{
		temp = bfr->next;
		if (!i && !ft_strcmp(bfr->key, hold))
			return (add_node(bfr, temp, hold, 0));
		else if (temp && !ft_strcmp(temp->key, hold))
			return (add_node(temp, bfr, hold, 1));
		bfr = bfr->next;
		i++;
	}
	free(hold);
	return (0);
}