/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:45:55 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/08 23:05:20 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_node(t_exp *bfr, t_exp *temp, char *hold)
{
	g_global_data.exported_vars = temp;
	free(bfr->key);
	free(bfr);
	free(hold);
	return (1);
}

int	middle_node(t_exp *temp, t_exp *bfr, char *hold)
{
	bfr->next = temp->next;
	free(temp->key);
	free(temp);
	free(hold);
	return (1);
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
			return (first_node(bfr, temp, hold));
		else if (temp && !ft_strcmp(temp->key, hold))
			return (middle_node(temp, bfr, hold));
		bfr = bfr->next;
		i++;
	}
	free(hold);
	return (0);
}
