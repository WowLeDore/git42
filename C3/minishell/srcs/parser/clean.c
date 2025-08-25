/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:00:14 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/25 17:26:44 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker(t_minishell *shell)
{
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;
	t_token	*tok;
	int		check;

	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		check = 0;
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			tok = tmp_tok;
			while (tmp_tok->type >= HEREDOC && tok && tok->type != WORDS)
				tok = tok->next;
			if (tmp_tok->type >= HEREDOC && (!tok || tok->type != WORDS))
				return (1);
			check = ((check == 1) || (tmp_tok->type == WORDS));
			tmp_tok = tmp_tok->next;
		}
		if (!check)
			return (1);
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}

void	remove_zero(t_pipe *pipe)
{
	t_token	*tmp_tok;
	t_token	*to_free;

	while (pipe->toks && !pipe->toks->size)
	{
		free_tok(pipe->toks->subs);
		to_free = pipe->toks;
		pipe->toks = pipe->toks->next;
		free(to_free);
	}
	tmp_tok = pipe->toks;
	while (tmp_tok && tmp_tok->next)
	{
		if (!tmp_tok->next->size)
		{
			free_tok(tmp_tok->next->subs);
			to_free = tmp_tok->next;
			tmp_tok->next = tmp_tok->next->next;
			free(to_free);
		}
		tmp_tok = tmp_tok->next;
	}
}

void	remove_quote(t_token *tok)
{
	t_token	*sub;
	t_token	*to_free;

	while (tok->subs && tok->subs->type <= DQUOTE)
	{
		to_free = tok->subs;
		tok->subs = tok->subs->next;
		free(to_free);
		tok->size--;
	}
	sub = tok->subs;
	while (sub && sub->next)
	{
		if (sub->next->type <= DQUOTE)
		{
			to_free = sub->next;
			sub->next = sub->next->next;
			free(to_free);
			tok->size--;
		}
		else
			sub = sub->next;
	}
}

void	clean(t_minishell *shell)
{
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;

	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			remove_quote(tmp_tok);
			tmp_tok = tmp_tok->next;
		}
		remove_zero(tmp_pipe);
		tmp_pipe = tmp_pipe->next;
	}
}
