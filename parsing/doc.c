/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:22:37 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/01 16:59:37 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// there mustn't be an operator preceding another

// "HELLO $NAME"
// "$NAME WELCOME"
// "Hello from $NAME to Mars"
// "> out > out2"
// echo $"USER"
// << $VAR

// #include "../minishell.h"

// void	var_expansion(t_env *env, char *token)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;
// 	char	*expansion;

// 	i = 0;
// 	tmp = NULL;
// 	while (token[i] && token[i] != '$')
// 		i++;
// 	if (!token[i])
// 		return;
// 	if (i)
// 		tmp = ft_substr(token, 0, i - 1);
// 	j = i + 1;
// 	while (token[j] && !is_expansion_separator(token[j]))
// 		j++;
// 	expansion = get_expansion(env, ft_substr(token, i + 1, j - 1));
// 	token = ft_strjoin(tmp, expansion);
// 	if (!tmp)
// 		free(expansion);
// 	if (token[j])
// 	{
// 		token = ft_strjoin(token, ft_substr(token, j, ft_strlen(token + j)));
// 		var_expansion(env, token);
// 	}
// }