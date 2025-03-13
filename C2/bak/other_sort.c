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

void	bubble(t_icq *a, t_icq *b)
{
	int	start;
	int	fst;
	int	snd;

	start = icq_tete(a);
	ra(a, b, 1);
	while (icq_tete(a) != start)
	{
		if (icq_tete(a) < start)
			start = icq_tete(a);
		ra(a, b, 1);
	}
	while (icq_tete(a) != start)
		ra(a, b, 1);
	while (!icq_sorted(a))
	{
		fst = a->last->next->num;
		snd = a->last->next->next->num;
		if (snd < fst && snd != start)
			sa(a, b, 1);
		ra(a, b, 1);
	}
	(void) b;
}

void	to_end(t_icq *a, t_icq *b, int end)
{
	int	count1;
	int	count2;

	count1 = 0;
	count2 = 0;
	while (icq_tete(b) != end)
		rb(a, b, 0 * count1++);
	while (count2 < count1)
		rrb(a, b, 0 * count2++);
	count2 = 0;
	while (icq_tete(b) != end)
		rrb(a, b, 0 * count2++);
	if (count1 > count2)
	{
		while (count2)
			write(1, "rrb\n", 4 + 0 * count2--);
	}
	else
	{
		while (count1)
			write(1, "rb\n", 3 + 0 * count1--);
	}
	rb(a, b, 1);
}

void	selection(t_icq *a, t_icq *b)
{
	int	end;

	end = icq_tete(a);
	pb(a, b, 1);
	while (!icq_vide(a))
	{
		if (icq_tete(a) > icq_tete(b))
			pb(a, b, 1);
		else if (icq_tete(a) < end)
		{
			end = icq_tete(a);
			pb(a, b, 1);
			rb(a, b, 1);
		}
		else
		{
			while (icq_tete(a) < icq_tete(b))
				rb(a, b, 1);
			pb(a, b, 1);
			to_end(a, b, end);
		}
	}
	while (!icq_vide(b))
		pa(a, b, 1);
}
