/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:50:05 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/22 22:47:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;

	i = 2;
	while (i <= nb / 2 && i <= 46340)
	{
		if (nb % i++ == 0)
			return (0);
	}
	if (nb < 2)
		return (0);
	return (1);
}
/*
#include <stdio.h>
#include <stdlib.h> 
int	main(int argc,char **argv)
{
	if (argc == 2)
		printf("prime(%d) : %d\n", atoi(argv[1]),
		ft_is_prime(atoi(argv[1])));
}
*/
