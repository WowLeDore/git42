/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:13:45 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/20 18:56:03 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_comm(t_comm *comm)
{
	comm->next = NULL;
	comm->word = NULL;
	comm->options = NULL;
	comm->ins = NULL;
	comm->outs = NULL;
	comm->appends = NULL;
	comm->heredoc = NULL;
	comm->builtin = 0;
}

int	alloc_list(size_t len, char ***list)
{
	if (len)
		*list = malloc(sizeof(char *) * (len + 1));
	return (len && !*list);
}

int	count_comms(t_token	*tmp_tok, t_comm *tmp_comm)
{
	size_t	len_op;
	size_t	len_in;
	size_t	len_ou;
	size_t	len_ap;

	len_op = 0;
	len_in = 0;
	len_ou = 0;
	len_ap = 0;
	while (tmp_tok)
	{
		len_op += tmp_tok->type == WORDS;
		len_in += tmp_tok->type == IN;
		len_ou += tmp_tok->type == OUT;
		len_ap += tmp_tok->type == APPEND;
		if (tmp_tok->type == HEREDOC)
			tmp_comm->heredoc = tmp_tok->heredoc;
		tmp_tok = tmp_tok->next;
	}
	return (alloc_list(len_op, &tmp_comm->options)
		|| alloc_list(len_in, &tmp_comm->ins)
		|| alloc_list(len_ou, &tmp_comm->outs)
		|| alloc_list(len_ap, &tmp_comm->appends));
}

int	alloc_comms(t_minishell *shell)
{
	t_comm	*tmp_comm;
	t_pipe	*tmp_pipe;

	init_comm(shell->comms);
	tmp_pipe = shell->pipes;
	tmp_comm = shell->comms;
	while (tmp_pipe)
	{
		if (count_comms(tmp_pipe->toks, tmp_comm))
			return (1);
		tmp_pipe = tmp_pipe->next;
		if (tmp_pipe)
		{
			tmp_comm->next = malloc(sizeof(t_comm));
			if (!tmp_comm->next)
				return (1);
			init_comm(tmp_comm->next);
		}
		else
			tmp_comm->next = NULL;
		tmp_comm = tmp_comm->next;
	}
	return (0);
}

int	make_commands(t_minishell *shell)
{
	t_comm	*tmp_comm;
	t_pipe	*tmp_pipe;
	char	*ptr;

	shell->big_str = malloc(sizeof(char) * big_len(shell));
	if (!shell->big_str)
		return (1);
	big_copy(shell);
	shell->comms = NULL;
	if (heredoc(shell))
		return (1);
	shell->comms = malloc(sizeof(t_comm));
	if (!shell->comms || alloc_comms(shell))
		return (1);
	tmp_pipe = shell->pipes;
	tmp_comm = shell->comms;
	ptr = shell->big_str;
	while (tmp_pipe)
	{
		ptr = assign_comms(tmp_pipe->toks, tmp_comm, ptr);
		tmp_pipe = tmp_pipe->next;
		tmp_comm = tmp_comm->next;
	}
	return (0);
}
