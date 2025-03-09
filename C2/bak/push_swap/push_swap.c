/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:23:22 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/07 19:27:30 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*s_to_l(char *str)
{
	int		nb;
	int		*l;

	nb = verif_format(str);
	if (!nb || !verif_all_nbr(str))
		return (NULL);
	while (str)
	{
		printf("%d\n", ft_atoi(str));
		str = ft_strchr(str, ' ');
		(void) (str && str++);
	}
}

int	main(int argc, char **argv)
{
	int	*a;

	if (argc < 2)
		return (0);
	if (argc == 2 && ft_strchr(argv[1], ' '))
		a = s_to_l(argv[1]);
	//else
	//	a = sl_to_l(argc - 1, argv + 1);
	if (!a)
		return (1 + 0 * write(2, "Error\n", 6));
	//sort(a);
}
