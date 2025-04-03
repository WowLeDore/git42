/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/03 15:34:19 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_icq *a, t_icq *b, t_icq *ope)
{
	t_maillon	*tmp;

	tmp = a->last;
	while (tmp && tmp->next != a->last)
		tmp = tmp->next;
	a->last = tmp;
	if (ope)
		icq_enfile(ope, 8, 0);
	(void) b;
}

void	rrb(t_icq *a, t_icq *b, t_icq *ope)
{
	t_maillon	*tmp;

	tmp = b->last;
	while (tmp && tmp->next != b->last)
		tmp = tmp->next;
	b->last = tmp;
	if (ope)
		icq_enfile(ope, 9, 0);
	(void) a;
}

void	rrr(t_icq *a, t_icq *b, t_icq *ope)
{
	rra(a, b, 0);
	rrb(a, b, 0);
	if (ope)
		icq_enfile(ope, 10, 0);
}
