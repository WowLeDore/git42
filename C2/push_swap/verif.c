/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:19:13 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/09 01:33:07 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	verif_nbr(char *nbr, int end)
{
	return ((*nbr == '-' && (end < 11 || ft_strncmp(MIN, nbr, end) > 0))
		|| (*nbr != '-' && (end < 10 || ft_strncmp(MAX, nbr, end) > 0)));
}

int	verif_all_nbr(char *str)
{
	char	*nxt;

	nxt = ft_strchr(str, ' ');
	if (nxt)
		return (verif_nbr(str, nxt - str) && verif_all_nbr(nxt + 1));
	return (verif_nbr(str, ft_strlen(str)));
}

int	verif_list(int i, char **str)
{
	return (!i || (verif_format(*str) && verif_nbr(*str, ft_strlen(*str))
			&& verif_list(--i, ++str)));
}

int	verif_format(char *str)
{
	int	nb;

	nb = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		nb++;
		if ((*str == '-' && (*(str + 1) < '0' || *(str + 1) > '9'))
			|| (*str != '-' && (*str < '0' || *str > '9')))
			return (0);
		str++;
		while (*str >= '0' && *str <= '9')
			str++;
		if (*str && (*(str++) != ' ' || !*str))
			return (0);
	}
	return (nb);
}

int	verif_duplicates(t_icq *q)
{
	t_maillon	*current;
	t_maillon	*compare;

	if (!q->size)
		return (1);
	current = q->last->next;
	while (current != q->last)
	{
		compare = current->next;
		while (compare != q->last->next)
		{
			if (current->num == compare->num)
				return (0);
			compare = compare->next;
		}
		current = current->next;
	}
	return (1);
}
