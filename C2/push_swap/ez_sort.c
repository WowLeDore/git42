/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ez_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:43:59 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/28 14:50:33 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	sorted(t_icq *q)
{
	t_maillon	*tmp;

	tmp = q->last->next;
	while (tmp != q->last)
	{
		if (tmp->num > tmp->next > num)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
void	sort_2(t_icq *q, t_icq *ops)
{
	
}
