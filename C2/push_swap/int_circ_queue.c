/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_circ_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:17:18 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/09 00:35:42 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	icq_init(t_icq *q)
{
	q->size = 0;
	q->last = NULL;
}

int	icq_vide(t_icq *q)
{
	return (q->size == 0);
}

void	icq_enfile(t_icq *q, int valeur, int reverse)
{
	t_maillon	*new;

	new = malloc(sizeof(t_maillon));
	if (!new)
		return ;
	new->num = valeur;
	if (icq_vide(q))
	{
		new->next = new;
		q->last = new;
	}
	else
	{
		new->next = q->last->next;
		q->last->next = new;
		if (reverse)
			q->last = new;
	};
}

int	icq_defile(t_icq *q)
{
	int			value;
	t_maillon	*temp;

	if (icq_vide(q))
		return (-2147483648);
	temp = q->last->next;
	value = temp->num;
	q->last->next = temp->next;
	free(temp);
	if (q->size == 1)
		q->last = NULL;
	q->size--;
	return (value);
}

int	icq_tete(t_icq *q)
{
	if (icq_vide(q))
		return (-2147483648);
	return (q->last->next->num);
}
