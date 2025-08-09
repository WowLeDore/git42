/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:16:41 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/09 19:20:09 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_coms(t_command *coms, char *str)
{
	coms->next = NULL;
	coms->word = str;
	coms->toks = malloc(sizeof(t_token));
	if (!coms->toks)
		return (1);
	coms->toks->next = NULL;
	coms->toks->type = NONTYPE;
	coms->toks->indx = 0;
	coms->toks->size = 0;
	return (0);
}

int	init_toks(t_token **toks)
{
	(*toks)->next = malloc(sizeof(t_token));
	if (!(*toks)->next)
		return (1);
	(*toks) = (*toks)->next;
	(*toks)->next = NULL;
	(*toks)->type = NONTYPE;
	(*toks)->indx = 0;
	(*toks)->size = 0;
	return (0);
}

int	handle_quote(int quote, char c)
{
	if (quote == 0 && c == '\'')
		quote = 1;
	else if (quote == 0 && c == '"')
		quote = 2;
	else if (quote == 1 && c == '\'')
		quote = 0;
	else if (quote == 2 && c == '"')
		quote = 0;
	return (quote);
}

int	handle_char(int quote, t_command *coms, size_t i, t_token **tmp_tok)
{
	if (quote == 0 && (coms->word[i] == '<' || coms->word[i] == '>'
			|| coms->word[i] == ' ' || coms->word[i] == '\t'))
	{
		if ((*tmp_tok)->type != NONTYPE && init_toks(tmp_tok))
			return (1);
		if (coms->word[i] == '<')
			(*tmp_tok)->type = IN;
		else if (coms->word[i] == '>')
			(*tmp_tok)->type = OUT;
		else if (coms->word[i] == ' ' || coms->word[i] == '\t')
			(*tmp_tok)->type = META;
		(*tmp_tok)->indx = i;
		(*tmp_tok)->size = 1;
		if (coms->word[i + 1] && coms->word[i + 1] != '|'
			&& init_toks(tmp_tok))
			return (1);
	}
	else
	{
		if ((*tmp_tok)->type == NONTYPE)
			(*tmp_tok)->indx = i;
		(*tmp_tok)->type = WORDS;
		(*tmp_tok)->size++;
	}
	return (0);
}

int	spliter(t_command *coms)
{
	size_t	i;
	int		quote;
	t_token	*tmp_tok;

	i = 0;
	quote = 0;
	tmp_tok = coms->toks;
	while (coms->word[i])
	{
		quote = handle_quote(quote, coms->word[i]);
		if (quote == 0 && coms->word[i] == '|')
		{
			coms->next = malloc(sizeof(t_command));
			if (!coms->next || init_coms(coms->next, coms->word + i + 1))
				return (1);
			return (spliter(coms->next));
		}
		else if (handle_char(quote, coms, i, &tmp_tok))
			return (1);
		i++;
	}
	return (0);
}
