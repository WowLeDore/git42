/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 05:50:46 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/21 05:54:55 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}
/*
#include <stdio.h>
#include <stdlib.h> 
int	main(int argc,char **argv)
{
	if (argc == 3)
		printf("%d ^ %d = %d\n", atoi(argv[1]), atoi(argv[2]),
		ft_recursive_power(atoi(argv[1]),atoi(argv[2])));
}
*/
