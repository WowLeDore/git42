/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/07 19:09:00 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_icq *a, t_icq *b, char out)
{
	t_maillon	*tmp;

	tmp = a->last;
	while (tmp && tmp->next != a->last)
		tmp = tmp->next;
	a->last = tmp;
	if (out)
		write(1, "rra\n", 4);
	(void) b;
}

void	rrb(t_icq *a, t_icq *b, char out)
{
	t_maillon	*tmp;

	tmp = b->last;
	while (tmp && tmp->next != b->last)
		tmp = tmp->next;
	b->last = tmp;
	if (out)
		write(1, "rrb\n", 4);
	(void) a;
}

void	rrr(t_icq *a, t_icq *b, char out)
{
	rra(a, b, 0);
	rrb(a, b, 0);
	if (out)
		write(1, "rrr\n", 4);
}
