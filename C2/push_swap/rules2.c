/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/11 09:26:11 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_icq *a, t_icq *b, int output)
{
	if (!icq_vide(a))
		a->last = a->last->next;
	if (output)
		write(1, "ra\n", 3);
	(void) b;
}

void	rb(t_icq *a, t_icq *b, int output)
{
	if (!icq_vide(b))
		b->last = b->last->next;
	if (output)
		write(1, "rb\n", 3);
	(void) a;
}

void	rr(t_icq *a, t_icq *b, int output)
{
	ra(a, b, 0);
	rb(a, b, 0);
	if (output)
		write(1, "rr\n", 3);
}
