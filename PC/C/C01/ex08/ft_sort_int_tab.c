/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:09:18 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/16 11:23:55 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	*small;
	int	*big;
	int	small_iter;
	int	big_iter;

	small = tab;
	small_iter = 0;
	while (small_iter < size - 1)
	{
		big = small;
		big_iter = small_iter + 1;
		while (big_iter < size)
		{
			big++;
			big_iter++;
			if (*small > *big)
				ft_swap(small, big);
		}
		small++;
		small_iter++;
	}
}

//#include <stdio.h>
//int main(){int arr[7]={6,5,4,3,2,1,0};int *tab=arr;ft_sort_int_tab(tab,7);
//for(int i=0;i<7;i++){printf("%d",tab[i]);};}
