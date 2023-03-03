/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:59:11 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/03 15:33:09 by ebelkhei         ###   ########.fr       */
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

int	check_digits(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (1);
	while (str[i] && !is_expansion_separator(str[i]))
		i++;
	return (i);
}

int	must_expand(int a, int b)
{
	if (a == '$' && b == '?')
		return (1);
	if (a == '$' && !is_expansion_separator(b))
		return (1);
	return (0);
}

void	var_expansion(t_env *env, t_token *tok)
{
	int		i;
	int		j;
	char	*tmp[3];
	char	*expansion;

	i = 0;
	tmp[0] = NULL;
	tmp[2] = NULL;
	while (tok->content[i] && !must_expand(tok->content[i], tok->content[i + 1]))
		i++;
	if (!tok->content[i] || !tok->content[i + 1])
		return ;
	if (i)
		tmp[0] = ft_substr(tok->content, 0, i);
	j = i + 1 + check_digits(tok->content + i + 1);
	expansion = get_expansion(env, ft_substr(tok->content, i + 1, j - i - 1));
	tmp[1] = ft_strjoin(tmp[0], expansion);
	free(expansion);
	if (ft_strlen(tok->content + j))
		tmp[2] = ft_substr(tok->content, j, ft_strlen(tok->content + j));
	free(tok->content);
	tok->content = ft_strjoin(tmp[1], tmp[2]);
	ft_free(tmp[1], tmp[2]);
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
	if ((token->type == DOUBLE || token->type == WORD) && ft_strlen(token->content) > 1)
		var_expansion(env, token);
}

int	ft_join(t_token **token, t_token *bef)
{
	if ((*token)->type == SPACE || (*token)->type == PIPE || (*token)->type == OPERATOR)
		return (0);
	if (!bef || bef->type == SPACE || bef->type == PIPE || bef->type == OPERATOR)
		return (0);
	else
	{
		bef->content = ft_strjoin(bef->content, (*token)->content);
		bef->next = (*token)->next;
		ft_lstdelone(*token);
		*token = bef->next;
		return (1);
	}

}

void	ignore_exp_here_doc(t_token *tok)
{
	while (tok)
	{
		if (ft_strlen(tok->content) == 1 && *tok->content == '$')
		{
			if (tok->next && (tok->next->type == DOUBLE || tok->next->type == SINGLE))
			{
				free(tok->content);
				tok->content = ft_strdup("");
			}
		}
		else if (ft_strlen(tok->content) == 2 && !ft_strcmp(tok->content, "<<"))
		{
			if (tok->next && tok->next->type == SPACE)
			{
				if(tok->next->next)
				{
					if (tok->next->next->type == WORD)
						tok->next->next->type = SINGLE_EXPAND;
					else
						tok->next->next->type = SINGLE;
				}
			}
			else if (tok->next)
			{
				if (tok->next->type == WORD)
					tok->next->type = SINGLE_EXPAND;
				else
					tok->next->type = SINGLE;
			}
		}
		tok = tok->next;
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