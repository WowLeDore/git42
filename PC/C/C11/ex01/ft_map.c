/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:29:54 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/03 16:10:00 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int	i;
	int	*mapped;

	mapped = malloc(sizeof(int) * length);
	if (mapped == NULL)
		return (NULL);
	i = -1;
	while (++i < length)
		mapped[i] = (*f)(tab[i]);
	return (mapped);
}
/*
#include <stdio.h>

int	multiply_by_two(int nb)
{
	return (2 * nb);
}

int	main()
{
	int	tab[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int	*tab2;
	
	
	tab2 = ft_map(tab, 20, &multiply_by_two);
	for (int i = 0; i < 20; i++)
		printf("%d\n", tab2[i]);
}
*/
