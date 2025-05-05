/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:08:03 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/05 13:56:47 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ez_sort(t_icq *a, t_icq *ops)
{
	t_icq	*b;

	b = malloc(sizeof(t_icq));
	if (!b)
		return (1);
	if (a->size == 2)
		sa(a, ops);
	else if (a->size == 3)
		sort_3(a, b, ops);
	else if (a->size == 4)
		sort_4(a, b, ops);
	else if (a->size == 5)
		sort_5(a, b, ops);
	free_all(b);
	return (a->size <= 5);
}

void	hidded_sort(t_icq *q)
{
	int			i;
	int			j;
	int			swp;
	t_maillon	*tmp1;
	t_maillon	*tmp2;

	i = -1;
	while (++i < q->size - 1)
	{
		tmp1 = q->last->next;
		j = -1;
		while (++j < q->size - 1)
		{
			tmp2 = tmp1->next;
			if (tmp1->num > tmp2->num)
			{
				swp = tmp1->num;
				tmp1->num = tmp2->num;
				tmp2->num = swp;
			}
			tmp1 = tmp1->next;
		}
	}
}

void	get_med_sorted(t_icq *q, int meds[DIVS][2])
{
	t_maillon	*tmp;
	int			i;
	int			count;

	tmp = q->last->next;
	i = 0;
	meds[0][0] = tmp->num;
	count = 1;
	while (1)
	{
		if ((count++ % (q->size / DIVS + 1)) == 0 && i < DIVS)
		{
			meds[i][1] = tmp->next->num;
			meds[++i][0] = tmp->num;
		}
		if (tmp == q->last)
			break ;
		tmp = tmp->next;
	}
	while (i < DIVS)
	{
		meds[i][1] = q->last->num;
		meds[++i][0] = q->last->num;
	}
	meds[DIVS - 1][1] = q->last->num;
}

int	left(t_icq *q, int lows[2], int highs[2], t_icq *ops)
{
	int			found;
	t_maillon	*tmp;

	tmp = q->last;
	found = 0;
	if ((lows[0] <= tmp->num && tmp->num <= highs[0])
		|| (lows[1] <= tmp->num && tmp->num <= highs[1]))
		found = 1;
	tmp = tmp->next;
	while (tmp != q->last)
	{
		if ((lows[0] <= tmp->num && tmp->num <= highs[0])
			|| (lows[1] <= tmp->num && tmp->num <= highs[1]))
			found = 1;
		tmp = tmp->next;
	}
	if (found && !((lows[0] <= icq_tete(q) && icq_tete(q) <= highs[0])
			|| (lows[1] <= icq_tete(q) && icq_tete(q) <= highs[1])))
		ra(q, ops);
	return (found);
}

void	pre_tri(t_icq *a, t_icq *b, int meds[DIVS][2], t_icq *ops)
{
	int	i;
	int	lows[2];
	int	highs[2];

	i = -1;
	while (++i < DIVS / 2)
	{
		lows[0] = meds[(DIVS / 2 - 1) - i][0];
		lows[1] = meds[(DIVS / 2 - 1) - i][1];
		highs[0] = meds[(DIVS / 2 + 0) + i][0];
		highs[1] = meds[(DIVS / 2 + 0) + i][1];
		while (a->last && left(a, lows, highs, ops))
		{
			if (lows[0] <= icq_tete(a) && icq_tete(a) <= highs[0])
				pb(a, b, ops);
			if (lows[1] <= icq_tete(a) && icq_tete(a) <= highs[1])
			{
				pb(a, b, ops);
				rb(b, ops);
			}
		}
	}
}
