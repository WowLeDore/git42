/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conquer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:03:34 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/10 17:03:38 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_icq *a, int best_i, t_icq *ops)
{
	if (best_i <= a->size / 2)
		while (best_i-- > 0)
			ra(a, ops);
	else
		while (best_i++ < a->size)
			rra(a, ops);
}

int	min_diff(t_icq *q, int value, int *best_i)
{
	int			i;
	int			size;
	int			diff;
	int			min_diff;
	t_maillon	*tmp;

	i = 0;
	min_diff = 0;
	size = q->size;
	tmp = q->last->next;
	while (size--)
	{
		diff = tmp->num - value;
		if (diff > 0 && (diff < min_diff || min_diff == 0))
		{
			min_diff = diff;
			*best_i = i;
		}
		tmp = tmp->next;
		i++;
	}
	if (min_diff == 0)
		*best_i = 0;
	return (min_diff);
}

void	insert(t_icq *a, t_icq *b, int size, t_icq *ops)
{
	t_maillon	*tmp;
	int			i;
	int			min;
	int			best_i;

	if (b->size == 0)
		return ;
	if (!min_diff(a, icq_tete(b), &best_i))
	{
		tmp = a->last->next;
		min = tmp->num;
		i = -1;
		while (++i < size)
		{
			if (tmp->num < min)
				best_i = i;
			if (tmp->num < min)
				min = tmp->num;
			tmp = tmp->next;
		}
	}
	rotate(a, best_i, ops);
	pa(a, b, ops);
}

void	sort_med(t_icq *a, t_medians *meds, t_icq *ops)
{
	t_icq	*b;

	b = malloc(sizeof(t_icq));
	if (!b)
		return ;
	icq_init(b);
	pre_tri(a, b, meds, ops);
	while (a->size > 1)
		pb(a, b, ops);
	pa(a, b, ops);
	while (b->size)
		insert(a, b, a->size, ops);
	while (a->last->num < icq_tete(a))
		ra(a, ops);
	free(b);
}

void	sort(t_icq *q, t_icq *ops)
{
	t_icq		*s;
	t_maillon	*tmp;
	t_medians	meds;

	s = malloc(sizeof(t_icq));
	if (!s)
		return ;
	icq_init(s);
	tmp = q->last;
	icq_enfile(s, tmp->num, 0);
	tmp = tmp->next;
	while (tmp != q->last)
	{
		icq_enfile(s, tmp->num, 0);
		tmp = tmp->next;
	}
	hidded_sort(s);
	get_med_sorted(s, &meds);
	while (s->size)
		icq_defile(s);
	free(s);
	sort_med(q, &meds, ops);
}
