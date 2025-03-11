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

void	sa(t_icq *a, t_icq *b)
{
	int	tmp;

	(void) b;
	tmp = icq_tete(a);
	a->last->next->num = a->last->next->next->num;
	a->last->next->next->num = tmp;
}

void	sb(t_icq *a, t_icq *b)
{
	int	tmp;

	(void) a;
	tmp = icq_tete(b);
	b->last->next->num = b->last->next->next->num;
	b->last->next->next->num = tmp;
}

void	ss(t_icq *a, t_icq *b)
{
	sa(a, b);
	sb(a, b);
}

void	pa(t_icq *a, t_icq *b)
{
	if (!icq_vide(b))
		icq_enfile(a, icq_defile(b));
}

void	pb(t_icq *a, t_icq *b)
{
	if (!icq_vide(a))
		icq_enfile(b, icq_defile(a));
}
