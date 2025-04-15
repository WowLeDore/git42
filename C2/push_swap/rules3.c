/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/15 16:08:36 by mguillot         ###   ########.fr       */
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
	if (ops && a->size > 1)
		icq_enfile(ops, RRA, 0);
}

void	rrb(t_icq *b, t_icq *ops)
{
	t_maillon	*tmp;

	tmp = b->last;
	while (tmp && tmp->next != b->last)
		tmp = tmp->next;
	b->last = tmp;
	if (ops && b->size > 1)
		icq_enfile(ops, RRB, 0);
}

void	rrr(t_icq *a, t_icq *b, t_icq *ops)
{
	rra(a, NULL);
	rrb(b, NULL);
	if (ops && a->size > 1 && b->size > 1)
		icq_enfile(ops, RRR, 0);
}
