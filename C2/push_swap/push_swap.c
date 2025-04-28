/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/28 14:40:53 by mguillot         ###   ########.fr       */
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

int	clean_exit(t_icq *q, t_icq *ops, t_icq *out, int status)
{
	if (q)
		free_all(q);
	if (ops)
		free_all(ops);
	if (out)
		free_all(out);
	if (status)
		write(2, "Error\n", 6);
	return (status);
}

t_icq	*parse(int argc, char **argv)
{
	t_icq	*q;

	if (argc == 1 && ft_strchr(*argv, ' '))
		q = s_to_l(*argv);
	else
		q = sl_to_l(argc, argv);
	if (q && verif_duplicates(q))
		return (q);
	clean_exit(q, NULL, NULL, 1);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_icq	*q;
	t_icq	*ops;
	t_icq	*out;

	if (argc < 2)
		return (1);
	q = parse(argc - 1, ++argv);
	if (!q)
		return (1);
	ops = malloc(sizeof(t_icq));
	if (!ops)
		return (clean_exit(q, NULL, NULL, 1));
	icq_init(ops);
	if (!ez_sort(q, ops))
		sort(q, ops);
	out = malloc(sizeof(t_icq));
	if (!out)
		return (clean_exit(q, ops, NULL, 1));
	icq_init(out);
	push_swap(ops, out);
	simplify(out);
	while (out->size)
		print_rules(icq_defile(out));
	return (clean_exit(q, ops, out, 0));
}
