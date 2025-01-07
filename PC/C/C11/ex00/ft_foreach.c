/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:17:41 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/03 16:09:17 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	i = 0;
	while (i < length)
		(*f)(tab[i++]);
}
/*
#include <unistd.h>

void	put_nbr(int nb)
{
	int		len;
	int		nb_copy;
	char	digit;

	len = 1;
	nb_copy = nb;
	while (nb_copy > 9)
	{
		nb_copy /= 10;
		len *= 10;
	}
	while (len > 0)
	{
		digit = (nb / len) % 10 + 48;
		len /= 10;
		write(1, &digit, 1);
	}
	write(1, "\n", 1);
}

int main()
{
	int	tab[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	ft_foreach(tab, 20, &put_nbr);
}
*/
