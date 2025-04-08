/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:05:34 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/09 00:38:53 by anonymous        ###   ########.fr       */
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
	q = malloc(sizeof(t_icq));
	if (!q)
		return (NULL);
	icq_init(q);
	while (str)
	{
		icq_enfile(q, ft_atoi(str), 1);
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
	q = malloc(sizeof(t_icq));
	if (!q)
		return (NULL);
	icq_init(q);
	while (count)
	{
		icq_enfile(q, ft_atoi(*(nbrs++)), 1);
		count--;
	}
	return (q);
}

int	main(int argc, char **argv)
{
	t_icq	*q;
	t_icq	*ops;
	t_icq	*out;

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
			icq_defile(q);
		free(q);
		return (1 + 0 * write(2, "Error\n", 6));
	}
	ops = malloc(sizeof(t_icq));
	if (!ops)
		return (1 + 0 * write(2, "Error\n", 6));
	sort(q, ops);
	while (!icq_vide(q))
		icq_defile(q);
	free(q);
	icq_init(ops);
	out = malloc(sizeof(t_icq));
	if (!out)
		return (1 + 0 * write(2, "Error\n", 6));
	icq_init(out);
	push_swap(ops, out);
	while (out->size)
		print_rules(icq_defile(out));
	return (0);
}
