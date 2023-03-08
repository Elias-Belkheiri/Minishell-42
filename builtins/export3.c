/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:25:33 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/09 00:22:33 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alphanum(char *s)
{
	int	i;

	i = 0;
	if (s && !(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z')
		&& s[i] != '_')
		return (0);
	while (s && s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && !(s[i] >= 'a' && s[i] <= 'z')
			&& !(s[i] >= 'A' && s[i] <= 'Z') && s[i] != '_')
		{
			if (s[i] == '=' || s[i] == '+')
				return (i);
			else
				return (0);
		}
		i++;
	}
	return (-1);
}

void	print_export(t_env **env)
{
	t_env	*temp;
	t_exp	*exp;

	temp = *env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	exp = g_global_data.exported_vars;
	while (exp)
	{
		if (exp->key)
			printf("%s\n", exp->key);
		exp = exp->next;
	}
}

void	plus_none_existed_var(t_env **env, int r, char *add)
{
	t_env	*new;
	t_env	*temp;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
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

int	free_them(char **hold)
{
	free(hold[0]);
	free(hold[1]);
	return (1);
}

int	exist_in_env(t_env **env, char *add)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, add))
			return (1);
		temp = temp->next;
	}
	return (0);
}
