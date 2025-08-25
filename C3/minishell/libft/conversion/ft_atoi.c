/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:57:14 by pbona             #+#    #+#             */
/*   Updated: 2024/12/01 17:54:05 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	n;

	sign = 1;
	n = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		n = n * 10 + *str - '0';
		str++;
	}
	return (sign * n);
}
/*
#include <stdio.h>

int 	main(int ac, char *av[])
{
	if (ac == 2)
		printf("%d\n",ft_atoi(av[1]));
	return (0);
}*/
