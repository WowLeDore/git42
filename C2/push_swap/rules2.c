/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/15 16:08:37 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_icq *a, t_icq *ops)
{
	if (a->size)
		a->last = a->last->next;
	if (ops && a->size > 1)
		icq_enfile(ops, RA, 0);
}

void	rb(t_icq *b, t_icq *ops)
{
	if (b->size)
		b->last = b->last->next;
	if (ops && b->size > 1)
		icq_enfile(ops, RB, 0);
}

void	rr(t_icq *a, t_icq *b, t_icq *ops)
{
	ra(a, NULL);
	rb(b, NULL);
	if (ops && a->size > 1 && b->size > 1)
		icq_enfile(ops, RR, 0);
}
