/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:51:24 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/15 16:13:42 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_comb(void)
{
	char	nb_noo;
	char	nb_ono;
	char	nb_oon;

	nb_noo = '0';
	while (nb_noo <= '7')
	{
		nb_ono = nb_noo + 1;
		while (nb_ono <= '8')
		{
			nb_oon = nb_ono + 1;
			while (nb_oon <= '9')
			{
				write(1, &nb_noo, 1);
				write(1, &nb_ono, 1);
				write(1, &nb_oon, 1);
				if (nb_noo != '7' || nb_ono != '8' || nb_oon != '9')
					write(1, ", ", 2);
				nb_oon++;
			}
			nb_ono++;
		}
		nb_noo++;
	}
}

//int main(){ft_print_comb();}
