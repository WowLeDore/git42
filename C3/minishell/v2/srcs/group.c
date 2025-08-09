/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:17:58 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/09 19:18:10 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	group_operators(t_minishell *shell)
{
	t_command	*tmp_com;
	t_token		*tmp_tok;
	void		*to_free;

	tmp_com = shell->coms;
	while (tmp_com)
	{
		tmp_tok = tmp_com->toks;
		while (tmp_tok)
		{
			if (tmp_tok->type >= IN && tmp_tok->next
				&& tmp_tok->next->type == tmp_tok->type)
			{
				to_free = (void *) tmp_tok->next;
				tmp_tok->next = tmp_tok->next->next;
				if (tmp_tok->type == IN)
					tmp_tok->type = HEREDOC + 0 * tmp_tok->size++;
				else
					tmp_tok->type = APPEND + 0 * tmp_tok->size++;
				free((t_token *) to_free);
			}
			tmp_tok = tmp_tok->next;
		}
		tmp_com = tmp_com->next;
	}
}

int	next_remove(t_token *tmp_tok)
{
	void		*to_free;

	if (!tmp_tok->next || tmp_tok->next->type != META)
		return (0);
	to_free = (void *) tmp_tok->next;
	tmp_tok->next = tmp_tok->next->next;
	free((t_token *) to_free);
	return (1);
}

void	remove_meta(t_minishell *shell)
{
	t_command	*tmp_com;
	t_token		*tmp_tok;

	tmp_com = shell->coms;
	while (tmp_com)
	{
		tmp_tok = tmp_com->toks;
		while (tmp_tok && tmp_tok->type == META)
		{
			tmp_com->toks = tmp_com->toks->next;
			free(tmp_tok);
			tmp_tok = tmp_com->toks;
		}
		while (tmp_tok)
		{
			if (!next_remove(tmp_tok))
				tmp_tok = tmp_tok->next;
		}
		tmp_com = tmp_com->next;
	}
}

void	group_redirections(t_minishell *shell)
{
	t_command	*tmp_com;
	t_token		*tmp_tok;
	void		*to_free;

	tmp_com = shell->coms;
	while (tmp_com)
	{
		tmp_tok = tmp_com->toks;
		while (tmp_tok)
		{
			if (tmp_tok->type >= HEREDOC)
			{
				tmp_tok->indx = tmp_tok->next->indx;
				tmp_tok->size = tmp_tok->next->size;
				to_free = (void *) tmp_tok->next;
				tmp_tok->next = tmp_tok->next->next;
				free((t_token *) to_free);
			}
			tmp_tok = tmp_tok->next;
		}
		tmp_com = tmp_com->next;
	}
}
