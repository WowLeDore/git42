/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:56:44 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/12 17:56:54 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tok(t_token *tok)
{
	t_token	*tmp_tok;
	void	*to_free;

	tmp_tok = tok;
	while (tmp_tok)
	{
		free_tok(tmp_tok->subs);
		to_free = (void *) tmp_tok;
		tmp_tok = tmp_tok->next;
		free((t_token *) to_free);
	}
}

int	free_all(t_minishell *shell, int value)
{
	t_pipe	*tmp_pipe;
	void	*to_free;

	if (!shell)
		return (value);
	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		free_tok(tmp_pipe->toks);
		to_free = (void *) tmp_pipe;
		tmp_pipe = tmp_pipe->next;
		free((t_pipe *) to_free);
	}
	return (value);
}

void	free_env(char ***env)
{
	size_t	i;

	i = 0;
	while (*env && (*env)[i])
		free((*env)[i++]);
	if (*env)
		free(*env);
}
