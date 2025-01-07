/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:05:42 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/04 19:13:01 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_doop.h"

bool	verif_op(char *str)
{
	if ((str[0] == '+' || str[0] == '-' || str[0] == '/'
			|| str[0] == '*' || str[0] == '%') && !str[1])
		return (true);
	return (false);
}

bool	verif_nbr(char *str)
{
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
		str++;
	return (*str >= '0' && *str <= '9');
}

int	a_to_i(char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
		sign *= 2 * (*str++ != '-') - 1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	return (res * sign);
}

int	main(int argc, char *argv[])
{
	int	val1;
	int	val2;

	if (argc != 4)
		return (0);
	if (!verif_op(argv[2]))
		write(1, "0\n", 2);
	if (!verif_op(argv[2]))
		return (0);
	if (verif_nbr(argv[1]) && !verif_nbr(argv[3]))
		put_nbr(a_to_i(argv[1]));
	if (!verif_nbr(argv[1]) && verif_nbr(argv[3]))
		put_nbr(a_to_i(argv[3]));
	if (!verif_nbr(argv[1]) || !verif_nbr(argv[3]))
		return (0);
	val1 = a_to_i(argv[1]);
	val2 = a_to_i(argv[3]);
	put_res(val1, val2, *(argv[2]));
	return (0);
}
