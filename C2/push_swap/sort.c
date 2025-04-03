/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:03:57 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/03 16:31:10 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	opti(t_icq *ope)
{
	t_maillon	*tmp;

	tmp = ope->last;
	while (tmp && tmp->next != ope->last && ope->size > 1)
	{
		if (tmp->num == tmp->next->num
			&& (tmp->num == 0 || tmp->num == 1 || tmp->num == 2))
			(void) (icq_defile(ope) + icq_defile(ope));
		tmp = tmp->next;
	}
}

void	op2(t_maillon *tmp)
{
	if (tmp->num == 8)
		write(1, "rra\n", 4);
	if (tmp->num == 9)
		write(1, "rrb\n", 4);
	if (tmp->num == 10)
		write(1, "rrr\n", 4);
}

void	op(t_icq *ope)
{
	t_maillon	*tmp;

	tmp = ope->last;
	while (tmp && tmp->next != ope->last)
	{
		if (tmp->num == 0)
			write(1, "sa\n", 3);
		if (tmp->num == 1)
			write(1, "sb\n", 3);
		if (tmp->num == 2)
			write(1, "ss\n", 3);
		if (tmp->num == 3)
			write(1, "pa\n", 3);
		if (tmp->num == 4)
			write(1, "pb\n", 3);
		if (tmp->num == 5)
			write(1, "ra\n", 3);
		if (tmp->num == 6)
			write(1, "rb\n", 3);
		if (tmp->num == 7)
			write(1, "rr\n", 3);
		op2(tmp);
		tmp = tmp->next;
	}
}

void	sort(t_icq *a)
{
	t_icq	*b;
	t_icq	*ope;

	b = malloc(sizeof(t_icq));
	if (!b)
		return ;
	ope = malloc(sizeof(t_icq));
	if (!ope)
		free(b);
	if (!ope)
		return ;
	icq_init(b);
	icq_init(ope);
	bubble(a, b, ope);
	opti(ope);
	op(ope);
	free(b);
	free(ope);
}
