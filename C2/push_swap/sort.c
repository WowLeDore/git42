/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:03:57 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/11 11:03:58 by mguillot         ###   ########.fr       */
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
			(void) icq_defile(ope) + icq_defile(ope);
		
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
