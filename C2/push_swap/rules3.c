/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/09 00:32:34 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_icq *a, t_icq *ops)
{
	t_maillon	*tmp;

	tmp = a->last;
	while (tmp && tmp->next != a->last)
		tmp = tmp->next;
	a->last = tmp;
	if (ops)
		icq_enfile(ops, RRA, 0);
}

void	rrb(t_icq *b, t_icq *ops)
{
	t_maillon	*tmp;

	tmp = b->last;
	while (tmp && tmp->next != b->last)
		tmp = tmp->next;
	b->last = tmp;
	if (ops)
		icq_enfile(ops, RRB, 0);
}

void	rrr(t_icq *a, t_icq *b, t_icq *ops)
{
	rra(a, NULL);
	rrb(b, NULL);
	if (ops)
		icq_enfile(ops, RRR, 0);
}
