/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:02:34 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/08 17:29:57 by anonymous        ###   ########.fr       */
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

void	pre_tri(t_icq *a, t_icq *b, int med)
{
	t_maillon	*tmp;

	while (1)
	{
		tmp = a->last->next;
		while (1)
		{
			if (tmp->num < med)
				break ;
			if (tmp == a->last)
				return ;
			tmp = tmp->next;
		}
		if (icq_tete(a) < med)
			pb(a, b, 1);
		else
			ra(a, b, 1);
	}
}
