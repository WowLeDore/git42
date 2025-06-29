/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:07:33 by pbona             #+#    #+#             */
/*   Updated: 2024/12/01 17:49:59 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	if (n == 0)
	{
		return (0);
	}
	while (*s1 && (unsigned char)*s1 == (unsigned char)*s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char *av[])
{
	if (ac == 4)
	{
		printf("%d\n",ft_strncmp(av[1], av[2], atoi(av[3])));
	}
	return (0);
}
*/
