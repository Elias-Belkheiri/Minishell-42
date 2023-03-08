/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:07:19 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/09 00:20:00 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_var(char *add, t_env **env, int r)
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
			break ;
		}
		free(tmp2);
		temp = temp->next;
	}
	if (!temp)
		plus_none_existed_var(env, r, add);
}

void	exported_vars(char *add, t_exp **exp, t_env **env)
{
	t_exp	*new;
	t_exp	*temp;

	temp = (*exp);
	if (exist_in_env(env, add))
		return ;
	while (temp && temp->next)
	{
		if (!ft_strcmp(temp->key, add))
			return ;
		temp = temp->next;
	}
	if (temp && !ft_strcmp(temp->key, add))
		return ;
	new = (t_exp *)ft_calloc(1, sizeof(t_exp));
	if ((*exp))
		temp->next = new;
	else
		(*exp) = new;
	new->key = ft_strdup(add);
	new->next = 0;
}

int	add_new_env_var(char *add, int r, t_env **temp, t_env **env)
{
	t_env	*new;
	char	*hold;

	if (check_if_exported(add, r))
		return (0);
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (*temp)
		(*temp)->next = new;
	else if (!(*env))
		(*env) = new;
	new->key = ft_substr(add, 0, r);
	hold = ft_substr(add, r + 1, ft_strlen(add) - r);
	new->value = to_trim(hold, " ");
	new->next = 0;
	free(hold);
	return (1);
}

int	check_arg(int r, char *add, t_env **env)
{
	t_env	*temp;
	char	*hold[2];

	temp = *env;
	if (add[r] == '=')
	{
		hold[0] = ft_substr(add, 0, r);
		while (temp && temp->next)
		{
			if (!ft_strcmp(hold[0], temp->next->key))
			{
				free (temp->next->value);
				hold[1] = ft_substr(add, r + 1, ft_strlen(add) - r);
				temp->next->value = to_trim(hold[1], " ");
				return (free_them(hold));
			}
			temp = temp->next;
		}
		free(hold[0]);
		if (!add_new_env_var(add, r, &temp, env))
			return (0);
	}
	else
		env_var(add, env, r);
	return (1);
}

int	export(t_env **env, char **add)
{
	int		i;

	i = 1;
	if (!add[1])
		print_export(env);
	while (add && add[i])
	{
		if (is_alphanum(add[i]) == -1)
			exported_vars(add[i], &(g_global_data.exported_vars), env);
		else if (!is_alphanum(add[i]))
			ft_dprintf("export: `%s': not a valid identifier\n", add[i]);
		else
		{
			if (!check_arg(is_alphanum(add[i]), add[i], env))
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
