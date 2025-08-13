/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:54:28 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/13 16:54:58 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	sub_handle_char(int quote, t_token *tok, size_t i, t_token **sub)
{
	if ((quote == 0 && (tok->word[i] == '"' || tok->word[i] == '\''))
		|| (quote == 1 && tok->word[i] == '\'')
		|| (quote == 2 && tok->word[i] == '"'))
	{
		if ((*sub)->type != NONTYPE && init_toks(sub))
			return (1);
		if (tok->word[i] == '\'')
			(*sub)->type = SQUOTE;
		else if (tok->word[i] == '"')
			(*sub)->type = DQUOTE;
		(*sub)->size = 1;
		(*sub)->word = tok->word + i;
		if (i + 1 < tok->size && init_toks(sub))
			return (1);
	}
	else
	{
		if ((*sub)->type == NONTYPE)
			(*sub)->word = tok->word + i;
		(*sub)->type = WORDS;
		(*sub)->size++;
	}
	return (0);
}

int	quote_split(t_token *tok)
{
	size_t	i;
	int		quote;
	t_token	*tmp_sub;

	tok->subs = malloc(sizeof(t_token));
	tmp_sub = tok->subs;
	if (!tmp_sub)
		return (1);
	tmp_sub->next = NULL;
	tmp_sub->type = NONTYPE;
	tmp_sub->size = 0;
	tmp_sub->word = NULL;
	tmp_sub->subs = NULL;
	i = 0;
	quote = 0;
	while (i < tok->size)
	{
		if (sub_handle_char(quote, tok, i, &tmp_sub))
			return (1);
		quote = handle_quote(quote, tok->word[i++]);
	}
	return (0);
}

int	sub_quote(t_minishell *shell)
{
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;

	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			if (quote_split(tmp_tok))
				return (1);
			tmp_tok = tmp_tok->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}
