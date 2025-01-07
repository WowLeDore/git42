/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_res.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:30:29 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/04 18:54:00 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doop.h"

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	put_str(char *str)
{
	write(1, str, str_len(str));
	write(1, "\n", 1);
}

void	rec_nbr(int nbr)
{
	char	c_nbr;

	c_nbr = nbr % 10 + '0';
	if (nbr < 10)
		write(1, &c_nbr, 1);
	else
	{
		rec_nbr(nbr / 10);
		rec_nbr(nbr % 10);
	}
}

void	put_nbr(int nbr)
{
	if (nbr < 0)
		write(1, "-", 1);
	if (nbr < 0)
		rec_nbr(-nbr);
	else
		rec_nbr(nbr);
	write(1, "\n", 1);
}

void	put_res(int a, int b, char op)
{
	if (op == '+')
		put_nbr(a + b);
	else if (op == '-')
		put_nbr(a - b);
	else if (op == '*')
		put_nbr(a * b);
	else if (b == 0)
	{
		if (op == '/')
			put_str("Stop : division by zero");
		else
			put_str("Stop : modulo by zero");
	}
	else if (op == '/')
		put_nbr(a / b);
	else
		put_nbr(a % b);
}
