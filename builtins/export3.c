/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:30:43 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/07 23:52:07 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env **env)
{
	t_exp	*exp;
	t_env	*temp;

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

int	set_node(char *add, int r, t_env *new)
{
	char	*key;

	new->key = ft_substr(add, 0, r);
	key = ft_substr(add, r + 1, ft_strlen(add) - r);
	new->value = to_trim(key, " ");
	new->next = 0;
	free(key);
	return (-1);
}
