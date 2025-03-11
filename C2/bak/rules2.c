/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/11 09:26:11 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_icq *a, t_icq *b)
{
	(void) b;
	if (!icq_vide(a))
		a->last = a->last->next;
}

void	rb(t_icq *a, t_icq *b)
{
	(void) a;
	if (!icq_vide(b))
		b->last = b->last->next;
}

void	rr(t_icq *a, t_icq *b)
{
	ra(a, b);
	rb(a, b);
}
