/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fralias      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:39:08 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/17 13:13:56 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_lenint(int n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_leadzero(int nb, int nb_zero)
{
	int		len;
	int		nb_copy;
	int		i;
	char	digit;

	i = nb_zero - ft_lenint(nb);
	while (i > 0)
	{
		write(1, "0", 1);
		i--;
	}
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
}

int	ft_maxnb(int n)
{
	if (n == 1)
		return (9);
	else if (n == 2)
		return (89);
	else if (n == 3)
		return (789);
	else if (n == 4)
		return (6789);
	else if (n == 5)
		return (56789);
	else if (n == 6)
		return (456789);
	else if (n == 7)
		return (3456789);
	else if (n == 8)
		return (23456789);
	return (123456789);
}

int	ft_verif(int nb)
{
	int	digit;
	int	prev_digit;

	while (nb > 0)
	{
		digit = nb % 10;
		nb /= 10;
		prev_digit = nb % 10;
		if (prev_digit >= digit)
			return (0);
	}
	return (1);
}

void	ft_print_combn(int n)
{
	int	i;
	int	n_copy;

	if (n == 9)
		write(1, "012345678, 012345679, 012345689, 012345789, 012346789,", 54);
	if (n == 9)
		write(1, " 012356789, 012456789, 013456789, 023456789, 123456789", 54);
	else
	{
		i = 1;
		n_copy = n - 2;
		while (n_copy > 0)
		{
			i *= 10;
			n_copy--;
		}
		while (i <= ft_maxnb(n) && ft_lenint(i) <= n)
		{
			if (ft_verif(i) == 1)
				ft_putnbr_leadzero(i, n);
			if (ft_verif(i) == 1 && i < ft_maxnb(n))
				write(1, ", ", 2);
			i++;
		}
	}
}

//int main(){for(int i=1;i<=9;i++){write(1,"\n\n",2);ft_print_combn(i);};}
