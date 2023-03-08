/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:45:55 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 23:53:55 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found(char *add, int r, t_env *temp, t_env *new)
{
	char	*hold;

	free (temp->next->value);
	hold = ft_substr(add, r + 1, ft_strlen(add) - r);
	temp->next->value = to_trim(hold, " ");
	free(hold);
	free(new);
	return (1);
}

int	add_new(char *add, int r, t_env **env, t_env *new)
{
	char	*key;
	t_env	*temp;

	key = ft_substr(add, 0, r);
	temp = (*env);
	while (temp && temp->next)
	{
		if (!ft_strcmp(key, temp->next->key))
		{
			free(key);
			return (found(add, r, temp, new));
		}
		temp = temp->next;
	}
	free(key);
	if (check_if_exported(add, r))
	{
		free(new);
		return (0);
	}
	if (temp)
		temp->next = new;
	else if (!(*env))
		(*env) = new;
	return (set_node(add, r, new));
}

void	plus_add_new(t_env **env, int r, char *add, t_env *new)
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
