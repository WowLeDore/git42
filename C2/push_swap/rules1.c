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

void	sa(t_icq *a, t_icq *b, t_icq *ope)
{
	int	tmp;

	tmp = icq_tete(a);
	a->last->next->num = a->last->next->next->num;
	a->last->next->next->num = tmp;
	if (ope)
		icq_enfile(ope, 0, 0);
	(void) b;
}

void	sb(t_icq *a, t_icq *b, t_icq *ope)
{
	int	tmp;

	tmp = icq_tete(b);
	b->last->next->num = b->last->next->next->num;
	b->last->next->next->num = tmp;
	if (ope)
		icq_enfile(ope, 1, 0);
	(void) a;
}

void	ss(t_icq *a, t_icq *b, t_icq *ope)
{
	sa(a, b, 0);
	sb(a, b, 0);
	if (ope)
		icq_enfile(ope, 2, 0);
}

void	pa(t_icq *a, t_icq *b, t_icq *ope)
{
	if (!icq_vide(b))
		icq_enfile(a, icq_defile(b), 0);
	if (ope)
		icq_enfile(ope, 3, 0);
}

void	pb(t_icq *a, t_icq *b, t_icq *ope)
{
	if (!icq_vide(a))
		icq_enfile(b, icq_defile(a), 0);
	if (ope)
		icq_enfile(ope, 4, 0);
}
