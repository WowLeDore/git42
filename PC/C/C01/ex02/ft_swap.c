/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:32:09 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/16 08:43:12 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

//#include <stdio.h>
//int main(){int a=42;int b=69;int *pt_to_a=&a;int *pt_to_b=&b;
//ft_swap(pt_to_a,pt_to_b);printf("%d",a);printf("%d",b);}
