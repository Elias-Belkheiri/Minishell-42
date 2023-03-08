/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:07:19 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 23:53:09 by hhattaki         ###   ########.fr       */
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
		plus_add_new(env, r, add, new);
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

int	check_arg(int r, char *add, t_env **env)
{
	t_env	*temp;
	t_env	*new;
	int		ret;

	temp = *env;
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (add[r] == '=')
	{
		ret = add_new(add, r, env, new);
		if (ret > -1)
			return (r);
	}
	else
		env_var(add, env, r, new);
	return (1);
}

int	export(t_env **env, char **add)
{
	int		i;
	int		r;

	i = 1;
	if (!add[1])
		print_export(env);
	while (add && add[i])
	{
		r = is_alphanum(add[i]);
		if (r == -1)
			exported_vars(add[i], &(g_global_data.exported_vars));
		else if (!r)
			ft_dprintf("export: `%s': not a valid identifier\n", add[i]);
		else
		{
			if (!check_arg(r, add[i], env))
			{
				while (i-- > 1)
					add++;
				export(env, add);
			}
		}
		i++;
	}
	return (0);
}
