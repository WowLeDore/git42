/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:02:34 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/09 00:25:50 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	get_med_sorted(t_icq *q, t_medians *meds)
{
	int	positions[DIVS - 1];
	int	i;
	int	j;

	i = -1;
	while (++i < DIVS - 1)
		positions[i] = ((i + 1) * q->size) / DIVS;
	i = 0;
	j = -1;
	while (++j < DIVS - 1)
	{
		while (i < positions[j])
		{
			ra(q, NULL);
			i++;
		}
		meds->values[DIVS - 2 - j] = icq_tete(q);
	}
}

int	found(t_icq *a, int med_low, int med_high, t_icq *ops)
{
	int			rot;
	t_maillon	*tmp;

	rot = -1;
	tmp = a->last->next;
	while (++rot < a->size)
	{
		if (tmp->num < med_low || tmp->num > med_high)
		{
			if (rot <= a->size / 2)
				while (rot-- > 0)
					ra(a, ops);
			else
				while (rot++ < a->size)
					rra(a, ops);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	pre_tri(t_icq *a, t_icq *b, t_medians *meds, int i, t_icq *ops)
{
	int	low;
	int	high;

	low = meds->values[DIVS - 2 - i];
	high = meds->values[i];
	while (1)
	{
		if (found(a, low, high, ops))
			break ;
		if (icq_tete(a) < low || icq_tete(a) > high)
			pb(a, b, ops);
		if (icq_tete(b) > high)
			rb(b, ops);
	}
}
