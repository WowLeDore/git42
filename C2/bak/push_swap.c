/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:23:22 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/10 17:53:22 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_icq	*s_to_l(char *str)
{
	int		nb;
	t_icq	*q;

	nb = verif_format(str);
	if (!nb || !verif_all_nbr(str))
		return (NULL);
	q = malloc(nb * sizeof(t_icq));
	init_icq(q);
	while (str)
	{
		icq_enfile(q, ft_atoi(str));
		str = ft_strchr(str, ' ');
		(void) (str && str++);
	}
	return (q);
}

t_icq	*sl_to_l(int count, char **nbrs)
{
	t_icq	*q;

	if (!verif_list(count, nbrs))
		return (NULL);
	q = malloc(count * sizeof(t_icq));
	init_icq(q);
	while (count)
	{
		icq_enfile(q, ft_atoi(*(nbrs++)));
		count--;
	}
	return (q);
}

int	sort(t_icq *a)
{
	while (!icq_vide(a))
		icq_dequeue(a);
	free(a);
	return (0);
}

int	main(int argc, char **argv)
{
	t_icq	*q;

	if (argc < 2)
		return (0);
	if (argc == 2 && ft_strchr(argv[1], ' '))
		q = s_to_l(argv[1]);
	else
		q = sl_to_l(argc - 1, argv + 1);
	if (!q)
		return (1 + 0 * write(2, "Error\n", 6));
	if (!verif_duplicates(q))
	{
		while (!icq_vide(q))
			icq_dequeue(q);
		free(q);
		return (1 + 0 * write(2, "Error\n", 6));
	}
	return (sort(q));
}
