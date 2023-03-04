/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:07:19 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/03 23:21:32 by hhattaki         ###   ########.fr       */
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

void	env_var(char *add, t_env *env, int r, t_env *new)
{
	char	*tmp2;
	t_env	*temp;

	if (add[r + 1] != '=')
	{
		ft_dprintf("export: `%s': not a valid identifier\n", add);
		free(new);
	}
	else
	{
		temp = env;
		while (temp)
		{
			tmp2 = ft_substr(add, 0, r);
			if (!ft_strcmp(tmp2, temp->key))
			{
				free(tmp2);
				tmp2 = ft_substr(add, r + 2, ft_strlen(add) - r - 2);
				temp->value = ft_strjoin(temp->value, tmp2);
				free(tmp2);
				free(new);
				break ;
			}
			free(tmp2);
			temp = temp->next;
		}
		if (!temp)
		{
			temp = env;
			while (temp->next)
				temp = temp->next;
			temp->next = new;
			new->key = ft_substr(add, 0, r);
			new->value = ft_substr(add, r + 2, ft_strlen(add) - r);
		}
	}
}

void	exported_vars(int r, char *add, t_env **exp)
{
	t_env	*new;
	t_env	*temp;

	if (!(*exp)->next)
	{
		(*exp)->key = add;
		(*exp)->value = 0;
		(*exp)->next = 0;
	}
	else if (!r)
		ft_dprintf("export: `%s': not a valid identifier\n", add);
	else
	{
		new = (t_env *)ft_calloc(1, sizeof(t_env));
		temp = (*exp);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->key = add;
		new->value = 0;
		new->next = 0;
	}
}

void	check_arg(char *add, t_env *env, t_env **exp)
{
	t_env	*temp;
	t_env	*new;
	int		r;

	r = is_alphanum(add);
	if (r == -1)
		exported_vars(r, add, exp);
	else
	{
		temp = env;
		new = (t_env *)ft_calloc(1, sizeof(t_env));
		if (add[r] == '=')
		{
			while (temp && temp->next)
				temp = temp->next;
			if (temp)
				temp->next = new;
			new->key = ft_substr(add, 0, r);
			new->value = ft_substr(add, r + 1, ft_strlen(add) - r);
			new->next = 0;
		}
		else
			env_var(add, env, r, new);
	}
}

int	export(t_env *env, char **add)
{
	// t_env	*exp;
	// t_env	*temp;
	int		i;

	i = 1;
	// exp = (t_env *)ft_calloc(1, sizeof(t_env));
	// if (!add[1])
	// {
	// 	temp = env;
	// 	while (temp)
	// 	{
	// 		printf("%s=%s\n", temp->value, temp->key);
	// 		temp = temp->next;
	// 	}
	// 	while (exp)
	// 	{
	// 		if (exp->key)
	// 			printf("%s=", exp->key);
	// 		if (exp->value)
	// 			printf("%s\n", exp->value);
	// 		exp = exp->next;
	// 	}
	// }
	while (add && add[i])
	{
		check_arg(add[i], env, NULL);
		i++;
	}
	return (0);
}