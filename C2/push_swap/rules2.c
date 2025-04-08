/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/09 00:32:21 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_icq *a, t_icq *ops)
{
	if (!icq_vide(a))
		a->last = a->last->next;
	if (ops)
		icq_enfile(ops, RA, 0);
}

void	rb(t_icq *b, t_icq *ops)
{
	if (!icq_vide(b))
		b->last = b->last->next;
	if (ops)
		icq_enfile(ops, RB, 0);
}

void	rr(t_icq *a, t_icq *b, t_icq *ops)
{
	ra(a, NULL);
	rb(b, NULL);
	if (ops)
		icq_enfile(ops, RR, 0);
}
