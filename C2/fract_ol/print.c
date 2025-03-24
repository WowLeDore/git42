/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:45:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/24 17:21:19 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	put_anb(long long snb, unsigned long long unb, char flag)
{
	int	printed;

	printed = 0;
	if (flag == 'c')
		return (write((int) unb, &snb, 1));
	if (flag == 'x' || flag == 'X')
	{
		if (unb > 15)
			printed = put_anb(snb, unb / 16, flag);
		if ((unb % 16) > 9)
			return (printed + put_anb((unb % 16) - 130 + flag + 'a', snb, 'c'));
		else
			return (printed + put_anb((unb % 16) + '0', snb, 'c'));
	}
	if (flag == 'd' || flag == 'i')
	{
		if (snb < 0)
			snb = -snb - ++printed + put_anb('-', unb, 'c');
		if (snb > 9)
			printed += put_anb(snb / 10, unb, flag);
		return (printed + put_anb((snb % 10) + '0', unb, 'c'));
	}
	if (unb > 9)
		return (put_anb(snb, unb / 10, flag) + put_anb(unb % 10 + 48, snb, 99));
	return (put_anb((unb % 10) + '0', snb, 'c'));
}

int	put_flg(int fd, char flag, va_list args, char null_check)
{
	unsigned long long	ptr;
	char				*str;

	if (flag == 's')
	{
		str = va_arg(args, char *);
		if (str && !*str)
			return (0);
		if (!null_check || str)
			return (ft_printfd(fd, "%c", *str) + ft_printfd(fd, "%s", str + 1));
		return (write(fd, "(null)", 6));
	}
	if (flag == 'p')
	{
		ptr = va_arg(args, unsigned long long);
		if (!null_check || ptr)
			return (write(fd, "0x", 2) + put_anb(fd, ptr, 'x'));
		return (write(fd, "(nil)", 5));
	}
	if (flag == 'd' || flag == 'i')
		return (put_anb(va_arg(args, int), fd, flag));
	if (flag == 'u' || flag == 'x' || flag == 'X')
		return (put_anb(fd, va_arg(args, unsigned int), flag));
	else
		return (put_anb(va_arg(args, int), fd, 'c'));
}

int	ft_printfd(int fd, const char *format, ...)
{
	int		printed;
	va_list	args;

	printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(++format) != '%')
			printed += put_flg(fd, *(format++), args, 1);
		else
			printed += ft_printfd(fd, "%c", *(format)++);
	}
	return (printed);
}
