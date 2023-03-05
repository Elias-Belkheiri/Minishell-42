/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:07:19 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/05 20:36:30 by hhattaki         ###   ########.fr       */
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

void	env_var(char *add, t_env **env, int r, t_env *new)
{
	char	*tmp2;
	t_env	*temp;

	temp = *env;
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
}

void	exported_vars(char *add, t_exp **exp)
{
	t_exp	*new;
	t_exp	*temp;

	new = (t_exp *)ft_calloc(1, sizeof(t_exp));
	temp = (*exp);
	while (temp && temp->next)
		temp = temp->next;
	if ((*exp))
		temp->next = new;
	else
		(*exp) = new;
	new->key = ft_strdup(add);
	new->next = 0;

}

void	check_arg(int r, char *add, t_env **env)
{
	t_env	*temp;
	char	*hold;
	char	*key;
	t_env	*new;

	temp = *env;
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (add[r] == '=')
	{
		key = ft_substr(add, 0, r);
		while (temp && temp->next)
		{
			if (!ft_strcmp(key, temp->next->key))
			{
				free (temp->next->value);
				hold = ft_substr(add, r + 1, ft_strlen(add) - r);
				temp->next->value = to_trim(hold, " ");
				free(hold);
				free(key);
				free(new);
				return ;
			}
			temp = temp->next;
		}
		free(key);
		if (temp)
			temp->next = new;
		else if (!(*env))
			(*env) = new;
		new->key = ft_substr(add, 0, r);
		hold = ft_substr(add, r + 1, ft_strlen(add) - r);
		new->value = to_trim(hold, " ");
		new->next = 0;
		free(hold);
	}
	else
		env_var(add, env, r, new);
}

int	export(t_env **env, char **add)
{
	t_exp	*exp;
	t_env	*temp;
	int		i;
	int		r;

	i = 1;
	if (!add[1])
	{
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
				printf("%s=\n", exp->key);
			exp = exp->next;
		}
	}
	while (add && add[i])
	{
		r = is_alphanum(add[i]);
		if (r == -1)
			exported_vars(add[i], &(g_global_data.exported_vars));
		else if (!r)
			ft_dprintf("export: `%s': not a valid identifier\n", add[i]);
		else
			check_arg(r, add[i], env);
		i++;
	}
	return (0);
}