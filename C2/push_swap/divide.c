/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:02:34 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/08 18:54:29 by anonymous        ###   ########.fr       */
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

	i = 0;
	while (i < q->size - 1)
	{
		tmp1 = q->last->next;
		j = 0;
		while (j < q->size - 1)
		{
			tmp2 = tmp1->next;
			if (tmp1->num > tmp2->num)
			{
				swp = tmp1->num;
				tmp1->num = tmp2->num;
				tmp2->num = swp;
			}
			tmp1 = tmp1->next;
			j++;
		}
		i++;
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
			ra(q, q, 0 * i++);
		meds->values[DIVS - j - 2] = icq_tete(q);
	}
}

void	pre_tri(t_icq *a, t_icq *b, int med_low, int med_high)
{
	int			rot;
	int			found;
	t_maillon	*tmp;

	while (1)
	{
		rot = -1;
		found = 0;
		tmp = a->last->next;
		while (++rot < a->size)
		{
			if (tmp->num < med_low || tmp->num > med_high)
			{
				found = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (!found)
			break ;
		if (rot <= a->size / 2)
			while (rot-- > 0)
				ra(a, b, 1);
		else
			while (rot++ < a->size)
				rra(a, b, 1);
		if (icq_tete(a) < med_low || icq_tete(a) > med_high)
			pb(a, b, 1);
		if (icq_tete(b) > med_high)
			rb(a, b, 1);
	}
}
