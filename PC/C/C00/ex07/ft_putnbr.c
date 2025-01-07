/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:35:31 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/15 19:36:12 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	ft_is_negative(int n)
{
	if (n < 0)
		return ('N');
	else
		return ('P');
}

void	ft_putnbr(int nb)
{
	int		len;
	long	long_nb;
	long	long_nb_copy;
	char	sign;
	char	digit;

	len = 1;
	sign = ft_is_negative(nb);
	long_nb = nb;
	if (long_nb < 0)
		long_nb = -long_nb;
	long_nb_copy = long_nb;
	while (long_nb_copy > 9)
	{
		long_nb_copy /= 10;
		len *= 10;
	}
	if (sign == 'N')
		write(1, "-", 1);
	while (len > 0)
	{
		digit = (long_nb / len) % 10 + 48;
		len /= 10;
		write(1, &digit, 1);
	}
}

//#include <limits.h>
//int main(){ft_putnbr(INT_MIN);ft_putnbr(-42);
//ft_putnbr(0);ft_putnbr(42);ft_putnbr(INT_MAX);}
