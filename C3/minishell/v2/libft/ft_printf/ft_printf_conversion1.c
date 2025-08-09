/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:00:34 by pbona             #+#    #+#             */
/*   Updated: 2025/02/08 14:15:23 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_c(va_list *args)
{
	char	c;

	c = va_arg(*args, int);
	write(1, &c, 1);
	return (1);
}

int	ft_s(va_list *args)
{
	char	*str;
	int		len;

	str = va_arg(*args, char *);
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

int	ft_d(va_list *args)
{
	int		len;
	int		i;
	long	nbr;
	char	num[12];

	nbr = va_arg(*args, int);
	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr < 0)
	{
		nbr = -nbr;
		len = ft_numlen(nbr, 10) + 1;
		num[0] = '-';
	}
	else
		len = ft_numlen(nbr, 10);
	i = len;
	num[i--] = '\0';
	while (nbr)
	{
		num[i--] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (write(1, num, len));
}

int	ft_i(va_list *args)
{
	return (ft_d(args));
}

int	ft_u(va_list *args)
{
	unsigned int	n;
	int				len;
	char			num[11];
	int				i;

	n = va_arg(*args, unsigned int);
	if (n == 0)
		return (write(1, "0", 1));
	len = ft_numlen(n, 10);
	i = len;
	num[i--] = '\0';
	while (n)
	{
		num[i--] = '0' + (n % 10);
		n /= 10;
	}
	return (write(1, num, len));
}
