/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:19:06 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/15 16:09:30 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_comb2(void)
{
	int		nb_nnnn;
	char	nb_nooo;
	char	nb_onoo;
	char	nb_oono;
	char	nb_ooon;

	nb_nnnn = 0;
	while (nb_nnnn <= 9999)
	{
		nb_nooo = (nb_nnnn / 1000) + '0';
		nb_onoo = ((nb_nnnn / 100) % 10) + '0';
		nb_oono = ((nb_nnnn / 10) % 10) + '0';
		nb_ooon = (nb_nnnn % 10) + '0';
		if (nb_nooo < nb_oono || (nb_nooo == nb_oono && nb_onoo < nb_ooon))
		{
			write(1, &nb_nooo, 1);
			write(1, &nb_onoo, 1);
			write(1, " ", 1);
			write(1, &nb_oono, 1);
			write(1, &nb_ooon, 1);
			if (nb_nnnn != 9899)
				write(1, ", ", 2);
		}
		nb_nnnn++;
	}
}

//int main(){ft_print_comb2();}
