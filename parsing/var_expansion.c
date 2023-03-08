/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:59:11 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/08 15:14:08 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expansion(t_env *env, char *key)
{
	char	*status;

	if (*key == '?')
	{
		free(key);
		status = ft_itoa(g_global_data.exit_status);
		g_global_data.exit_status = 0;
		return (status);
	}
	while (env && ft_strcmp(env->key, key))
		env = env->next;
	if (env && !ft_strcmp(env->key, key))
	{
		free(key);
		return (ft_strdup(env->value));
	}
	free(key);
	return (ft_strdup(""));
}

void	var_expansion(t_env *env, char **tok)
{
	int		i;
	int		j;
	char	*tmp[3];
	char	*expansion;
	char	*content;

	i = 0;
	tmp[0] = NULL;
	tmp[2] = NULL;
	content = *tok;
	while (content[i] && !must_expand(content[i], content[i + 1]))
		i++;
	if (!content[i] || !content[i + 1])
		return ;
	if (i)
		tmp[0] = ft_substr(content, 0, i);
	j = i + 1 + check_digits(content + i + 1);
	expansion = get_expansion(env, ft_substr(content, i + 1, j - i - 1));
	tmp[1] = ft_strjoin(tmp[0], expansion);
	if (ft_strlen(content + j))
		tmp[2] = ft_substr(content, j, ft_strlen(content + j));
	*tok = ft_strjoin(tmp[1], tmp[2]);
	ft_free(tmp[1], tmp[2], content, expansion);
	var_expansion(env, tok);
}

void	ft_trim(t_token *tok)
{
	char	*tmp;

	while (tok)
	{
		tmp = tok->content;
		if (!*tmp)
		{
			free (tmp);
			tok->content = ft_strdup("");
			return ;
		}
		if (tok->type == DOUBLE)
		{
			tok->content = ft_strtrim(tok->content, "\"");
			free(tmp);
		}
		if (tok->type == SINGLE)
		{
			tok->content = ft_strtrim(tok->content, "\'");
			free(tmp);
		}
		tok = tok->next;
	}
}

void	check_expansion(t_token *token, t_env *env)
{
	if (token->type == HYPHEN)
		hyphen_expansion(token, env);
	else if ((token->type == DOUBLE || token->type == WORD)
		&& ft_strlen(token->content) > 1)
	{
		if (*token->content == '$')
			token->expanded = 1;
		var_expansion(env, &token->content);
	}
}

void	expansion(t_token *token, t_env *env, t_token **tokens)
{
	t_token	*tmp;

	(void)tokens;
	(void)env;
	tmp = NULL;
	ft_trim(*tokens);
	ignore_exp_here_doc(*tokens);
	while (token)
	{
		check_expansion(token, env);
		if (!ft_join(&token, tmp))
		{
			tmp = token;
			token = token->next;
		}
	}
}
