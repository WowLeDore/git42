/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:00:20 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/22 15:42:48 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	sqrt;

	sqrt = 0;
	while (sqrt < 46340 && sqrt * sqrt < nb)
		sqrt++;
	if (sqrt * sqrt == nb)
		return (sqrt);
	return (0);
}
/*
#include <stdio.h>
#include <stdlib.h> 
int	main(int argc,char **argv)
{
	if (argc == 2)
		printf("sqrt(%d) : %d\n", atoi(argv[1]),
		ft_sqrt(atoi(argv[1])));
}
*/
