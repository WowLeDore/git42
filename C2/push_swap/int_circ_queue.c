/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_circ_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:08:01 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/15 16:08:20 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	icq_init(t_icq *q)
{
	q->size = 0;
	q->last = NULL;
}

void	icq_enfile(t_icq *q, int valeur, int reverse)
{
	t_maillon	*new;

	new = malloc(sizeof(t_maillon));
	if (!new)
		return ;
	new->num = valeur;
	if (q->size)
	{
		new->next = q->last->next;
		q->last->next = new;
		if (reverse)
			q->last = new;
	}
	else
	{
		new->next = new;
		q->last = new;
	}
	q->size++;
}

int	icq_defile(t_icq *q)
{
	int			value;
	t_maillon	*temp;

	if (!q->size)
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
	if (q->size)
		return (q->last->next->num);
	return (-2147483648);
}

void	free_all(t_icq *q)
{
	while (q->size)
		icq_defile(q);
	free(q);
}
