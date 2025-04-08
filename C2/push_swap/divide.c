/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:02:34 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/08 01:49:18 by mguillot         ###   ########.fr       */
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

void	get_med_sorted(t_icq *q, int *med_t1, int *med_t2)
{
	int	i;
	int	t1;
	int	t2;

	i = 0;
	t1 = (1 * q->size) / 3;
	t2 = (2 * q->size) / 3;
	while (i < t1)
		ra(q, q, 0 * i++);
	*med_t1 = icq_tete(q);
	while (i < t2)
		ra(q, q, 0 * i++);
	*med_t2 = icq_tete(q);
}

void	pre_tri(int tiers, t_icq *a, t_icq *b)
{
	if (tiers == 0)
		ra(a, b, 1);
	if (tiers == 1)
		pb(a, b, 1);
	if (tiers == 2)
	{
		pb(a, b, 1);
		rb(a, b, 1);
	}
}

int	stop_pre_tri(t_icq *q, int med)
{
	t_maillon	*tmp;

	tmp = q->last->next;
	while (1)
	{
		if (tmp->num > med)
			return (0);
		if (tmp == q->last)
			break ;
		tmp = tmp->next;
	}
	return (1);
}
