/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:45:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/20 23:39:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_nbr(int nbr)
{
	int	printed;

	if (nbr == -2147483648)
		return (put_str("-2147483648"));
	printed = 0;
	if (nbr < 0)
		printed = put_chr('-');
	if (nbr < 0)
		nbr = -nbr;
	if (nbr > 9)
		printed += put_nbr(nbr / 10);
	return (printed + put_chr((nbr % 10) + '0'));
}

int	put_unb(unsigned int unbr)
{
	if (unbr > 9)
		return (put_unb(unbr / 10) + put_chr((unbr % 10) + '0'));
	return (put_chr((unbr % 10) + '0'));
}

int	put_lhx(unsigned long long hex)
{
	int	printed;

	printed = 0;
	if (hex > 15)
		printed = put_lhx(hex / 16);
	if ((hex % 16) > 9)
		return (printed + put_chr((hex % 16) + 'a' - 10));
	else
		return (printed + put_chr((hex % 16) + '0'));
}

int	put_uhx(unsigned int hex)
{
	int	printed;

	printed = 0;
	if (hex > 15)
		printed = put_uhx(hex / 16);
	if ((hex % 16) > 9)
		return (printed + put_chr((hex % 16) + 'A' - 10));
	else
		return (printed + put_chr((hex % 16) + '0'));
}

int	ft_printf(const char *format, ...)
{
	int		printed;
	va_list	args;

	printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			printed += put_flg(*(++format), args);
		else
			printed += ft_printf("%c", *format);
		format++;
	}
	return (printed);
}
