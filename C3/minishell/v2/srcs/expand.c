/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:39:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/13 16:47:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_sub(t_token *tok, size_t size, char *word)
{
	t_token	*sub;

	sub = malloc(sizeof(t_token));
	if (!sub)
		return (NULL);
	sub->next = tok->next;
	sub->type = WORDS;
	sub->size = size;
	sub->word = word;
	sub->subs = NULL;
	return (sub);
}

int	expand(t_token *tk, char *value, char **env)
{
	size_t	j;

	j = 0;
	if (*tk->word == '?')
	{
		tk->type = XPNDED;
		tk->word = value;
		tk->size = ft_strlen(value) + j++;
	}
	else if (ft_isalpha(*tk->word) || *tk->word == '_')
		while (j < tk->size && (ft_isalnum(tk->word[j]) || tk->word[j] == '_'))
			j++;
	if (tk->type != XPNDED && get_env(env, tk->word, j))
	{
		tk->type = XPNDED;
		tk->word = get_env(env, tk->word, j);
		tk->size = ft_strlen(tk->word);
	}
	return (j);
}

int	handle_dollar(t_token **sub, size_t i, char *value, char **env)
{
	size_t	j;
	t_token	*tk;
	t_token	*tk2;

	tk = init_sub(*sub, (*sub)->size - i - 1, (*sub)->word + i + 1);
	if (!tk)
		return (1);
	j = expand(tk, value, env);
	(*sub)->next = tk;
	if (tk->type == XPNDED)
	{
		tk2 = init_sub(tk, (*sub)->size - i - 1 - j, (*sub)->word + i + 1 + j);
		if (!tk2)
			return (1);
		tk->next = tk2;
		(*sub)->size = i;
		(*sub) = (*sub)->next;
	}
	else
		(*sub)->size = i;
	return (0);
}

int	handle_word(t_token *subs, char *value, char **env)
{
	t_token	*tmp_sub;
	int		quote;
	size_t	i;

	tmp_sub = subs;
	quote = 0;
	while (tmp_sub)
	{
		if (quote != 1 && tmp_sub->type == WORDS)
		{
			i = 0;
			while (i < tmp_sub->size)
			{
				if (tmp_sub->word[i] == '$'
					&& handle_dollar(&tmp_sub, i, value, env))
					return (1);
				i++;
			}
		}
		if (tmp_sub->type == SQUOTE)
			quote = 1 - quote;
		tmp_sub = tmp_sub->next;
	}
	return (0);
}

int	expand_vars(t_minishell	*shell)
{
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;

	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			if (tmp_tok->type != HEREDOC
				&& handle_word(tmp_tok->subs, shell->value, shell->env))
				return (1);
			tmp_tok = tmp_tok->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}
