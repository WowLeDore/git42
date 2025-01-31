/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:45:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/21 16:04:26 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_anb(long long snb, unsigned long long unb, char flag)
{
	int	printed;

	printed = 0;
	if (flag == 'c')
		return (write(1, &snb, 1));
	if (flag == 'x' || flag == 'X')
	{
		if (unb > 15)
			printed = put_anb(snb, unb / 16, flag);
		if ((unb % 16) > 9)
			return (printed + put_anb((unb % 16) - 130 + flag + 'a', 0, 'c'));
		else
			return (printed + put_anb((unb % 16) + '0', 0, 'c'));
	}
	if (flag == 'd' | flag == 'i')
	{
		if (snb < 0)
			snb = -snb - ++printed + put_anb('-', 0, 'c');
		if (snb > 9)
			printed += put_anb(snb / 10, unb, flag);
		return (printed + put_anb((snb % 10) + '0', 0, 'c'));
	}
	if (unb > 9)
		return (put_anb(snb, unb / 10, flag) + put_anb(unb % 10 + '0', 0, 'c'));
	return (put_anb((unb % 10) + '0', 0, 'c'));
}

int	put_flg(char flag, va_list args, char null_check)
{
	unsigned long long	ptr;
	char				*str;

	if (flag == 's')
	{
		str = va_arg(args, char *);
		if (str && !*str)
			return (0);
		if (!null_check || str)
			return (ft_printf("%c", *str) + ft_printf("%s", str + 1));
		return (write(1, "(null)", 6));
	}
	if (flag == 'p')
	{
		ptr = va_arg(args, unsigned long long);
		if (!null_check || ptr)
			return (write(1, "0x", 2) + put_anb(0, ptr, 'x'));
		return (write(1, "(nil)", 5));
	}
	if (flag == 'd' || flag == 'i')
		return (put_anb(va_arg(args, int), 0, flag));
	if (flag == 'u' || flag == 'x' || flag == 'X')
		return (put_anb(0, va_arg(args, unsigned int), flag));
	else
		return (put_anb(va_arg(args, int), 0, 'c'));
}

int	ft_printf(const char *format, ...)
{
	int		printed;
	va_list	args;

	printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(++format) != '%')
			printed += put_flg(*(format++), args, 1);
		else
			printed += ft_printf("%c", *(format)++);
	}
	return (printed);
}
