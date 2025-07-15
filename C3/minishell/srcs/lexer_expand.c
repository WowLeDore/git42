/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:21:00 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/12 17:11:33 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	val_expnd(t_token_list *tokens, char value)
{
	tokens->word = &value;
	tokens->size = 1;
	if (value < 0)
		tokens->size = 2;
	if (value > 9 || value < -9)
		tokens->size++;
	if (value > 99 || value < -99)
		tokens->size++;
	tokens->type = T_VAL;
	return (0);
}

void	lex_expnd(t_token_list *tokens, char **env, int value)
{
	size_t	i;

	while (tokens)
	{
		if (tokens->type == T_VAR && tokens->word[0] != '?')
		{
			i = 0;
			while (env[i] && tokens->type == T_VAR)
			{
				if (!ft_strncmp(tokens->word, env[i], tokens->size)
					&& env[i][tokens->size] == '=')
				{
					tokens->word = env[i] + tokens->size + 1;
					tokens->size = ft_strlen(tokens->word);
					tokens->type = T_WORD;
				}
				i++;
			}
			tokens->size = (tokens->type != T_VAR) * tokens->size;
		}
		else if (tokens->type == T_VAR)
			val_expnd(tokens, value);
		tokens = tokens->next;
	}
}

t_token_list	*nxt_expnd(char *word, t_token_list *head, int group)
{
	t_token_list	*expnd;

	expnd = malloc(sizeof(t_token_list));
	if (!expnd)
		return (NULL);
	expnd->type = head->type;
	expnd->group = 0;
	if (head->type == T_XWORD)
		expnd->group = group;
	expnd->next = NULL;
	expnd->size = *word && (ft_isalpha(*word) || ft_strchr("_?", *word));
	if (*word && (ft_isalpha(*word) || *word == '_'))
		while (ft_isalnum(word[expnd->size])
			|| word[expnd->size] == '_')
			expnd->size++;
	expnd->word = word + expnd->size;
	expnd->size = head->word + head->size - word - expnd->size;
	return (expnd);
}

t_token_list	*var_expnd(t_token_list *head, int group)
{
	t_token_list	*expnd;

	expnd = malloc(sizeof(t_token_list));
	if (!expnd)
		return (NULL);
	expnd->word = ft_strchr(head->word, '$') + 1;
	expnd->next = NULL;
	expnd->size = ft_isalpha(*expnd->word) || ft_strchr("_?", *expnd->word);
	if (*expnd->word && (ft_isalpha(*expnd->word) || *expnd->word == '_'))
		while (ft_isalnum(expnd->word[expnd->size])
			|| expnd->word[expnd->size] == '_')
			expnd->size++;
	expnd->type = T_VAR;
	expnd->group = 0;
	if (head->type == T_XWORD)
		expnd->group = group;
	expnd->next = nxt_expnd(expnd->word, head, group);
	if (!expnd->next)
	{
		free(expnd);
		return (NULL);
	}
	head->size = ft_strchr(head->word, '$') - head->word;
	expnd->next->next = head->next;
	return (expnd);
}

int	mak_expnd(t_token_list	**head)
{
	t_token_list	*tmp;
	t_token_list	*expnd;
	size_t			groups;

	tmp = *head;
	groups = 0;
	while (tmp)
	{
		if (tmp->type != T_WORD
			&& ft_memchr(tmp->word, '$', tmp->size))
		{
			if (tmp->type == T_XWORD && !tmp->group)
				tmp->group = ++groups;
			expnd = var_expnd(tmp, groups);
			if (!expnd)
				return (1);
			tmp->next = expnd;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
