/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:51:18 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/10 16:22:49 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_rules(int rule)
{
	char	*rules[11];

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

void	reduce(t_icq *ops, t_icq *temp, int *changed)
{
	int		curr;
	int		next;

	while (ops->size > 0)
	{
		curr = icq_defile(ops);
		if (ops->size > 0)
		{
			next = icq_tete(ops);
			if ((curr == PA && next == PB) || (curr == PB && next == PA)
				|| (curr == RA && next == RRA) || (curr == RB && next == RRB))
			{
				icq_defile(ops);
				*changed = 1;
				continue ;
			}
		}
		icq_enfile(temp, curr, 0);
	}
}

void	simplify(t_icq *ops)
{
	int		changed;
	t_icq	*temp;

	changed = 0;
	temp = malloc(sizeof(t_icq));
	if (!temp)
		return ;
	icq_init(temp);
	reduce(ops, temp, &changed);
	while (temp->size > 0)
		icq_enfile(ops, icq_defile(temp), 0);
	free(temp);
	if (changed)
		simplify(ops);
}

void	push_swap(t_icq *ops, t_icq *out)
{
	int	a;
	int	b;

	while (ops->size > 0)
	{
		a = icq_defile(ops);
		if (ops->size == 0)
		{
			icq_enfile(out, a, 0);
			break ;
		}
		b = icq_tete(ops);
		if ((a == RA && b == RB) || (a == RB && b == RA)
			|| (a == RRA && b == RRB) || (a == RRB && b == RRA)
			|| (a == PA && b == PB) || (a == PB && b == PA))
		{
			icq_defile(ops);
			if (a == RA || a == RB)
				icq_enfile(out, RR, 0);
			else if (a == RRA || a == RRB)
				icq_enfile(out, RRR, 0);
		}
		else
			icq_enfile(out, a, 0);
	}
}
