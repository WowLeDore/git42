/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ez_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:43:59 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/05 13:33:29 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sorted(t_icq *q)
{
	t_maillon	*tmp;

	tmp = q->last->next;
	while (tmp != q->last)
	{
		if (tmp->num > tmp->next->num)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	sort_3(t_icq *a, t_icq *b, t_icq *ops)
{
	int	x;
	int	y;
	int	z;

	(void) b;
	x = icq_tete(a);
	y = a->last->next->next->num;
	z = a->last->num;
	if ((x < z && z < y) || (y < x && x < z) || (z < y && y < x))
		sa(a, ops);
	else if (y < z && z < x && x > y)
		ra(a, ops);
	else if (z < x && x < y && y > z)
		rra(a, ops);
	else
		return ;
	sort_3(a, b, ops);
}

void	sort_4(t_icq *a, t_icq *b, t_icq *ops)
{
	pb(a, b, ops);
	sort_3(a, b, ops);
	if (icq_tete(b) > a->last->next->next->num && icq_tete(b) < a->last->num)
		ra(a, ops);
	pa(a, b, ops);
	if (a->last->next->next->next->num > icq_tete(a) && !sorted(a))
		sa(a, ops);
	if (a->last->next->next->next->num > a->last->num)
		rra(a, ops);
	if (icq_tete(a) > a->last->next->next->num)
		ra(a, ops);
}

void	sort_5(t_icq *a, t_icq *b, t_icq *ops)
{
	int		tb;

	pb(a, b, ops);
	sort_4(a, b, ops);
	tb = icq_tete(b);
	if (tb > a->last->next->next->next->num && tb < a->last->num)
		rra(a, ops);
	if (tb > a->last->next->next->num && tb < a->last->num)
		ra(a, ops);
	pa(a, b, ops);
	if (icq_tete(a) < a->last->next->next->next->num && !sorted(a))
		sa(a, ops);
	if (a->last->next->next->next->num > a->last->num)
		rra(a, ops);
	if (!sorted(a))
		ra(a, ops);
	if (!sorted(a))
		ra(a, ops);
}
