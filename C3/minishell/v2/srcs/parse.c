/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:00:51 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/13 16:55:33 by mguillot         ###   ########.fr       */
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
			check = check == 1 || tmp_tok->type == WORDS;
			tmp_tok = tmp_tok->next;
		}
		if (!check)
			return (1);
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}

void	remove_zero(t_token	*tok)
{
	t_token	*sub;
	t_token	*to_free;

	while (tok->subs && !tok->subs->size)
	{
		to_free = tok->subs;
		tok->subs = tok->subs->next;
		free(to_free);
	}
	sub = tok->subs;
	while (sub && sub->next)
	{
		if (!sub->next->size)
		{
			to_free = sub->next;
			sub->next = sub->next->next;
			free(to_free);
		}
		else
			sub = sub->next;
	}
}

void	clean(t_minishell	*shell)
{
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;

	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			remove_zero(tmp_tok);
			tmp_tok = tmp_tok->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
}

int	parser(t_minishell *shell, char *str)
{
	shell->pipes = malloc(sizeof(t_pipe));
	if (!shell->pipes)
		return (free_all(shell, 1));
	if (init_pipe(shell->pipes, str) || spliter(shell->pipes))
		return (free_all(shell, 1));
	group_operators(shell);
	remove_meta(shell);
	if (checker(shell))
		// imprimer un message correspondant ici
		return (free_all(shell, 0));
	group_redirections(shell);
	if (sub_quote(shell))
		return (free_all(shell, 0));
	if (expand_vars(shell))
		return (free_all(shell, 0));
	clean(shell);
	//if (word_split(shell))
	//	return (free_all(shell, 0));
	//quote_remove(shell);
	print_minishell(shell);
	return (free_all(shell, 0));
}
