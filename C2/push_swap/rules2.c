/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/07 19:09:44 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_icq *a, t_icq *b, char out)
{
	if (!icq_vide(a))
		a->last = a->last->next;
	if (out)
		write(1, "ra\n", 3);
	(void) b;
}

void	rb(t_icq *a, t_icq *b, char out)
{
	if (!icq_vide(b))
		b->last = b->last->next;
	if (out)
		write(1, "rb\n", 3);
	(void) a;
}

void	rr(t_icq *a, t_icq *b, char out)
{
	ra(a, b, 0);
	rb(a, b, 0);
	if (out)
		write(1, "rr\n", 3);
}
