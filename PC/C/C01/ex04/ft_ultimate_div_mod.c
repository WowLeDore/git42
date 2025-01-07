/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:55:29 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/16 08:59:49 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	tmp;

	tmp = *a % *b;
	*a = *a / *b;
	*b = tmp;
}

//#include <stdio.h>
//int main(){int a=42;int b=7;int *pt_to_a=&a;int *pt_to_b=&b;
//ft_ultimate_div_mod(pt_to_a,pt_to_b);printf("%d",a);printf("%d",b);}
