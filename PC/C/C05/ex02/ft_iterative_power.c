/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 05:46:23 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/21 05:49:53 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	res;

	res = 1;
	while (power > 0)
	{
		res *= nb;
		power--;
	}
	if (power < 0)
		return (0);
	return (res);
}
/*
#include <stdio.h>
#include <stdlib.h> 
int	main(int argc,char **argv)
{
	if (argc == 3)
		printf("%d ^ %d = %d\n", atoi(argv[1]), atoi(argv[2]),
		ft_iterative_power(atoi(argv[1]),atoi(argv[2])));
}
*/
