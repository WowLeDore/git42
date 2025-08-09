/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:21:00 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/05 16:49:38 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	val_expnd(t_token_list *tokens, unsigned char value)
{
	*tokens->word = (char) value;
	tokens->size = 1;
	if (value > 9)
		tokens->size++;
	if (value > 99)
		tokens->size++;
	tokens->type = T_VAL;
	return (0);
}

void	lex_expnd(t_token_list *tokens, char **env, unsigned char value)
{
	while (tokens)
	{
		if (tokens->type == T_VAR && tokens->word[0] != '?')
		{
			tokens->word = get_env(env, tokens->word, tokens->size);
			if (!tokens->word)
				tokens->size = 0;
			else
				tokens->size = ft_strlen(tokens->word);
			if (!tokens->word)
				tokens->word = " ";
			else
				tokens->type = T_WORD;
		}
		else if (tokens->type == T_VAR)
			val_expnd(tokens, value);
		tokens = tokens->next;
	}
}

t_token_list	*nxt_expnd(char *word, t_token_list *head)
{
	t_token_list	*expnd;

	expnd = malloc(sizeof(t_token_list));
	if (!expnd)
		return (NULL);
	expnd->type = head->type;
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

t_token_list	*var_expnd(t_token_list *head)
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
	expnd->next = nxt_expnd(expnd->word, head);
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

	tmp = *head;
	while (tmp)
	{
		if (tmp->type != T_WORD
			&& ft_memchr(tmp->word, '$', tmp->size))
		{
			expnd = var_expnd(tmp);
			if (!expnd)
				return (1);
			tmp->next = expnd;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
