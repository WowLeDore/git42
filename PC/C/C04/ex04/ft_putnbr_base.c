/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbt_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 02:50:50 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/21 04:08:06 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_base_illegale(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		if (base[i] == '-' || base[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long	long_nbr;

	if (ft_strlen(base) <= 1 || ft_base_illegale(base))
		return ;
	long_nbr = nbr;
	if (long_nbr < 0)
		long_nbr = -long_nbr;
	if (nbr < 0)
		write(1, "-", 1);
	if (long_nbr < ft_strlen(base))
		write(1, &base[long_nbr], 1);
	else
	{
		ft_putnbr_base(long_nbr / ft_strlen(base), base);
		ft_putnbr_base(long_nbr % ft_strlen(base), base);
	}
}
/*
int	ft_atoi(char *str)
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

int	main(int argc,char **argv)
{
	if (argc == 3)
		ft_putnbr_base(ft_atoi(argv[1]), argv[2]);
}
*/
