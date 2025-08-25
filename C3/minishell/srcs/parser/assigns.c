/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:18:26 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/17 00:18:33 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	big_len(t_minishell *shell)
{
	size_t	i;
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;
	t_token	*tmp_sub;

	i = 0;
	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			tmp_sub = tmp_tok->subs;
			while (tmp_sub)
			{
				i += tmp_sub->size;
				tmp_sub = tmp_sub->next;
			}
			i++;
			tmp_tok = tmp_tok->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (i + 1);
}

void	big_copy(t_minishell *shell)
{
	size_t	i;
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;
	t_token	*tmp_sub;

	i = 0;
	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			tmp_sub = tmp_tok->subs;
			while (tmp_sub)
			{
				ft_memcpy(shell->big_str + i, tmp_sub->word, tmp_sub->size);
				i += tmp_sub->size;
				tmp_sub = tmp_sub->next;
			}
			shell->big_str[i++] = '\0';
			tmp_tok = tmp_tok->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	shell->big_str[i] = '\0';
}

void	null_last(size_t len, char **list)
{
	if (len)
		list[len] = NULL;
}

size_t	assign_list(char **list, t_type type, t_type wanted, char *ptr)
{
	if (type == wanted)
		*list = ptr;
	return (type == wanted);
}

char	*assign_comms(t_token *tok, t_comm *comm, char *ptr)
{
	size_t	len_op;
	size_t	len_in;
	size_t	len_ou;
	size_t	len_ap;

	len_op = 0;
	len_in = 0;
	len_ou = 0;
	len_ap = 0;
	while (tok)
	{
		len_op += assign_list(comm->options + len_op, tok->type, WORDS, ptr);
		len_in += assign_list(comm->ins + len_in, tok->type, IN, ptr);
		len_ou += assign_list(comm->outs + len_ou, tok->type, OUT, ptr);
		len_ap += assign_list(comm->appends + len_ap, tok->type, APPEND, ptr);
		ptr += ft_strlen(ptr) + 1;
		tok = tok->next;
	}
	if (comm->options)
		comm->word = *comm->options;
	null_last(len_op, comm->options);
	null_last(len_in, comm->ins);
	null_last(len_ou, comm->outs);
	null_last(len_ap, comm->appends);
	return (ptr);
}
