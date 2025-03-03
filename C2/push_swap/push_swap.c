/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:23:22 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/03 17:39:30 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int	*a;

	if (argc < 2)
		return (1 + 0 * ft_printf("Error"));
	if (argc == 2 && ft_strchr(argv[1], ' '))
		a = s_to_l(argv[1]);
	else
		a = sl_to_l(argc - 1, argv + 1);
	if (!a)
		return (1 + 0 * ft_printf("Error"));
	sort(a);
}
