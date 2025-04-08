/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conquer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:38:31 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/08 23:15:05 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_icq *a, t_icq *b, int best_i)
{
	if (best_i <= a->size / 2)
		while (best_i-- > 0)
			ra(a, b, 1);
	else
		while (best_i++ < a->size)
			rra(a, b, 1);
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

void	insert(t_icq *a, t_icq *b, int value, int size)
{
	t_maillon	*tmp;
	int			i;
	int			min;
	int			best_i;

	if (b->size == 0)
		return ;
	if (!min_diff(a, value, &best_i))
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
	rotate(a, b, best_i);
	pa(a, b, 1);
}

void	sort_med(t_icq *a, t_medians *meds)
{
	int		i;
	t_icq	*b;

	b = malloc(sizeof(t_icq));
	if (!b)
		return ;
	icq_init(b);
	i = -1;
	while (++i < DIVS / 2)
		pre_tri(a, b, meds, i);
	while (a->size - 1)
		pb(a, b, 1);
	pa(a, b, 1);
	while (b->size)
		insert(a, b, icq_tete(b), a->size);
	while (a->last->num < icq_tete(a))
		ra(a, b, 1);
	free(b);
}

void	sort(t_icq *q)
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
	sort_med(q, &meds);
}
