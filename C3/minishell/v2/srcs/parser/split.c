/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:16:41 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/18 15:44:26 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(t_pipe *pipe, char *str)
{
	pipe->next = NULL;
	pipe->word = str;
	pipe->toks = malloc(sizeof(t_token));
	if (!pipe->toks)
		return (1);
	pipe->toks->next = NULL;
	pipe->toks->type = NONTYPE;
	pipe->toks->size = 0;
	pipe->toks->word = NULL;
	pipe->toks->subs = NULL;
	pipe->toks->heredoc = NULL;
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
	(*toks)->size = 0;
	(*toks)->word = NULL;
	(*toks)->subs = NULL;
	(*toks)->heredoc = NULL;
	return (0);
}

int	handle_char(int quote, t_pipe *pipe, size_t i, t_token **tmp_tok)
{
	if (quote == 0 && (pipe->word[i] == '<' || pipe->word[i] == '>'
			|| pipe->word[i] == ' ' || pipe->word[i] == '\t'))
	{
		if ((*tmp_tok)->type != NONTYPE && init_toks(tmp_tok))
			return (1);
		if (pipe->word[i] == '<')
			(*tmp_tok)->type = IN;
		else if (pipe->word[i] == '>')
			(*tmp_tok)->type = OUT;
		else if (pipe->word[i] == ' ' || pipe->word[i] == '\t')
			(*tmp_tok)->type = META;
		(*tmp_tok)->word = pipe->word + i;
		(*tmp_tok)->size = 1;
		if (pipe->word[i + 1] && pipe->word[i + 1] != '|' && init_toks(tmp_tok))
			return (1);
	}
	else
	{
		if ((*tmp_tok)->type == NONTYPE)
			(*tmp_tok)->word = pipe->word + i;
		(*tmp_tok)->type = WORDS;
		(*tmp_tok)->size++;
	}
	return (0);
}

int	spliter(t_pipe *pipes)
{
	size_t	i;
	int		quote;
	t_token	*tmp_tok;

	i = 0;
	quote = 0;
	tmp_tok = pipes->toks;
	while (pipes->word[i])
	{
		quote = handle_quote(quote, pipes->word[i]);
		if (quote == 0 && pipes->word[i] == '|')
		{
			pipes->next = malloc(sizeof(t_pipe));
			if (!pipes->next || init_pipe(pipes->next, pipes->word + i + 1))
				return (1);
			return (spliter(pipes->next));
		}
		else if (handle_char(quote, pipes, i, &tmp_tok))
			return (1);
		i++;
	}
	return (0);
}
