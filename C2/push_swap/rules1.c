/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:26:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/09 01:32:10 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_icq *a, t_icq *ops)
{
	int	tmp;

	tmp = icq_tete(a);
	a->last->next->num = a->last->next->next->num;
	a->last->next->next->num = tmp;
	if (ops)
		icq_enfile(ops, SA, 0);
}

void	sb(t_icq *b, t_icq *ops)
{
	int	tmp;

	tmp = icq_tete(b);
	b->last->next->num = b->last->next->next->num;
	b->last->next->next->num = tmp;
	if (ops)
		icq_enfile(ops, SB, 0);
}

void	ss(t_icq *a, t_icq *b, t_icq *ops)
{
	sa(a, NULL);
	sb(b, NULL);
	if (ops)
		icq_enfile(ops, SS, 0);
}

void	pa(t_icq *a, t_icq *b, t_icq *ops)
{
	if (!b->size)
		return ;
	icq_enfile(a, icq_defile(b), 0);
	if (ops)
		icq_enfile(ops, PA, 0);
}

void	pb(t_icq *a, t_icq *b, t_icq *ops)
{
	if (!a->size)
		return ;
	icq_enfile(b, icq_defile(a), 0);
	if (ops)
		icq_enfile(ops, PB, 0);
}
