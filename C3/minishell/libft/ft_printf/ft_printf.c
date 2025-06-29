/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:00:12 by pbona             #+#    #+#             */
/*   Updated: 2025/04/24 19:32:06 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_conv(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	(*ft_get_function(char c))(va_list *args)
{
	int		(*f[9])(va_list *);
	char	*formats;
	int		i;

	i = 0;
	formats = "cspdiuxX%";
	f[0] = &ft_c;
	f[1] = &ft_s;
	f[2] = &ft_p;
	f[3] = &ft_d;
	f[4] = &ft_i;
	f[5] = &ft_u;
	f[6] = &ft_x;
	f[7] = &ft_xucase;
	f[8] = &ft_modulo;
	while (formats[i])
	{
		if (formats[i] == c)
		{
			return (f[i]);
		}
		i++;
	}
	return (NULL);
}

int	ft_print_conv(char c, va_list *args)
{
	int		(*func)(va_list *);

	func = ft_get_function(c);
	return (func(args));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (!format)
		return (-1);
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			if (ft_get_conv(format[i + 1]))
			{
				len += ft_print_conv(format[i + 1], &args);
				i++;
			}
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

/*#include <stdio.h>

int	main(void)
{
	int		ret1, ret2;

	printf("Printf    : ");
	ret1 = printf("\n", );
	printf("Return: %d\n", ret1);
	ft_printf("Ft_printf : ");
	ret2 = ft_printf("\n", );
	printf("Return: %d\n", ret2);

	return (0);
*/
