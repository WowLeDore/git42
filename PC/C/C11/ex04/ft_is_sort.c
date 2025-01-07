/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:15:45 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/03 16:22:54 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	i;

	i = 0;
	while (++i < length)
	{
		if ((*f)(tab[i - 1], tab[i]) > 0)
			return (0);
	}
	return (1);
}
/*
#include <stdio.h>
int	f(int a, int b)
{
	return (a - b);
}

int	main()
{
	int	tab1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	tab2[10] = {5, 6, 0, 1, 3, 4, 2, 9, 7, 8};

	printf("%d\n", ft_is_sort(tab1, 10, &f));
	printf("%d\n", ft_is_sort(tab2, 10, &f));
}
*/
