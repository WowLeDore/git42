/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:46:03 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/16 08:53:49 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a / b;
	*mod = a % b;
}

//#include <stdio.h>
//int main(){int a=42;int b=7;int div;int mod;int *pt_to_div=&div;
//int *pt_to_mod=&mod;ft_div_mod(a,b,pt_to_div,pt_to_mod);
//printf("%d",div);printf("%d",mod);}
