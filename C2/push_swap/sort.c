/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:38:31 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/07 20:29:05 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_med(t_icq *a, int med)
{
	t_icq	*b;

	b = malloc(sizeof(t_icq));
	if (!b)
		return ;
	icq_init(b);
	while (a->size - 1)
	{
		pb(a, b, 1);
		if (icq_tete(b) > med)
			rb(a, b, 1);
	}
	while (b->size)
	{
		while (icq_tete(b) > icq_tete(a))
			ra(a, b, 1)
		pb(a, b, 1);
	}
}

void	sort(t_icq *q)
{
	int			ante_med;
	int			post_med;
	t_maillon	*med;
	t_maillon	*tmp;

	med = q->last->next;
	while (1)
	{
		ante_med = 0;
		post_med = 0;
		tmp = q->last->next;
		while (1)
		{
			ante_med = ante_med + (tmp->num < med->num);
			post_med = post_med + (tmp->num > med->num);
			if (tmp == q->last)
				break ;
			tmp = tmp->next;
		}
		if (!((ante_med - post_med) / 2))
			break ;
		med = med->next;
	}
	sort_med(q, med->num);
}
