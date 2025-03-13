/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:03:57 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/11 11:03:58 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	icq_sorted(t_icq *q)
{
	int			count;
	t_maillon	*current;

	if (icq_vide(q) || q->size == 1)
		return (1);
	current = q->last->next;
	count = q->size - 1;
	while (count--)
	{
		if (current->num > current->next->num)
			return (0);
		current = current->next;
	}
	return (1);
}

void	bubble(t_icq *a, t_icq *b, t_icq *ope)
{
	int	start;
	int	fst;
	int	snd;

	start = icq_tete(a);
	ra(a, b, ope);
	while (icq_tete(a) != start)
	{
		if (icq_tete(a) < start)
			start = icq_tete(a);
		ra(a, b, ope);
	}
	while (icq_tete(a) != start)
		ra(a, b, ope);
	while (!icq_sorted(a))
	{
		fst = a->last->next->num;
		snd = a->last->next->next->num;
		if (snd < fst && snd != start)
			sa(a, b, ope);
		ra(a, b, ope);
	}
	(void) b;
}
