/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:00:51 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/09 19:20:15 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_all(t_minishell *shell, int value)
{
	t_token		*tmp_tok;
	t_command	*tmp_com;
	void		*to_free;

	if (!shell)
		return (value);
	tmp_com = shell->coms;
	while (tmp_com)
	{
		tmp_tok = tmp_com->toks;
		while (tmp_tok)
		{
			to_free = (void *) tmp_tok;
			tmp_tok = tmp_tok->next;
			free((t_token *) to_free);
		}
		to_free = (void *) tmp_com;
		tmp_com = tmp_com->next;
		free((t_command *) to_free);
	}
	return (value);
}

int	checker(t_minishell *shell)
{
	t_command	*tmp_com;
	t_token		*tmp_tok;
	int			check;

	tmp_com = shell->coms;
	while (tmp_com)
	{
		check = 0;
		tmp_tok = tmp_com->toks;
		while (tmp_tok)
		{
			if (tmp_tok->type >= HEREDOC
				&& (!tmp_tok->next || tmp_tok->next->type != WORDS))
				return (1);
			if (tmp_tok->type == WORDS)
				check = 1;
			tmp_tok = tmp_tok->next;
		}
		if (!check)
			return (1);
		tmp_com = tmp_com->next;
	}
	return (0);
}

int	parser(char *str, t_minishell *shell)
{
	shell->coms = malloc(sizeof(t_command));
	if (!shell->coms)
		return (free_all(shell, 1));
	if (init_coms(shell->coms, str) || spliter(shell->coms))
		return (free_all(shell, 1));
	group_operators(shell);
	remove_meta(shell);
	if (checker(shell))
		return (free_all(shell, 0));
	group_redirections(shell);
	print_minishell(shell);
	return (free_all(shell, 0));
}
