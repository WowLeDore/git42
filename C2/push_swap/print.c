/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:51:18 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/09 00:41:31 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_rules(int rule)
{
	char	*rules[10];

	rules[0] = "sa\n";
	rules[1] = "sb\n";
	rules[2] = "ss\n";
	rules[3] = "pa\n";
	rules[4] = "pb\n";
	rules[5] = "ra\n";
	rules[6] = "rb\n";
	rules[7] = "rr\n";
	rules[8] = "rra\n";
	rules[9] = "rrb\n";
	rules[10] = "rrr\n";
	if (rule > 7)
		write(1, rules[rule], 4);
	else
		write(1, rules[rule], 3);
}

void	push_swap(t_icq *ops, t_icq *out)
{
	int	a;
	int	b;

	while (ops->size > 0)
	{
		a = icq_defile(ops);
		if (ops->size == 0)
			return (icq_enfile(out, a, 0));
		b = icq_tete(ops);
		if ((a == RA && b == RB) || (a == RB && b == RA))
		{
			icq_defile(ops);
			icq_enfile(out, RR, 0);
		}
		else if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
		{
			icq_defile(ops);
			icq_enfile(out, RRR, 0);
		}
		else if ((a == RA && b == RRA) || (a == RRA && b == RA)
			|| (a == RB && b == RRB) || (a == RRB && b == RB))
			icq_defile(ops);
		else
			icq_enfile(out, a, 0);
	}
}
