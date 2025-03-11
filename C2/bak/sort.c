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

void	sort(t_icq *a)
{
	t_icq	*b;

	b = malloc(sizeof(t_icq));
	if (!b)
		return ;
	icq_init(b);
	selection(a, b);
	free(b);
}
