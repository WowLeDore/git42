/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/07 19:10:44 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_icq *a, t_icq *b, char out)
{
	int	tmp;

	tmp = icq_tete(a);
	a->last->next->num = a->last->next->next->num;
	a->last->next->next->num = tmp;
	if (out)
		write(1, "sa\n", 3);
	(void) b;
}

void	sb(t_icq *a, t_icq *b, char out)
{
	int	tmp;

	tmp = icq_tete(b);
	b->last->next->num = b->last->next->next->num;
	b->last->next->next->num = tmp;
	if (out)
		write(1, "sb\n", 3);
	(void) a;
}

void	ss(t_icq *a, t_icq *b, char out)
{
	sa(a, b, 0);
	sb(a, b, 0);
	if (out)
		write(1, "ss\n", 3);
}

void	pa(t_icq *a, t_icq *b, char out)
{
	if (!icq_vide(b))
		icq_enfile(a, icq_defile(b), 0);
	if (out)
		write(1, "pa\n", 3);
}

void	pb(t_icq *a, t_icq *b, char out)
{
	if (!icq_vide(a))
		icq_enfile(b, icq_defile(a), 0);
	if (out)
		write(1, "pb\n", 3);
}
