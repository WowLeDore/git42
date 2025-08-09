/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:00:42 by pbona             #+#    #+#             */
/*   Updated: 2025/02/08 19:53:29 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_x(va_list *args)
{
	unsigned int	n;
	int				len;
	char			num[9];
	int				i;

	n = va_arg(*args, unsigned int);
	if (n == 0)
		return (write(1, "0", 1));
	len = ft_numlen(n, 16);
	i = len;
	num[i--] = '\0';
	while (n)
	{
		num[i--] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	return (write(1, num, len));
}

int	ft_xucase(va_list *args)
{
	unsigned int	n;
	int				len;
	char			num[9];
	int				i;

	n = va_arg(*args, unsigned int);
	if (n == 0)
		return (write(1, "0", 1));
	len = ft_numlen(n, 16);
	i = len;
	num[i--] = '\0';
	while (n)
	{
		num[i--] = "0123456789ABCDEF"[n % 16];
		n /= 16;
	}
	return (write(1, num, len));
}

int	ft_p(va_list *args)
{
	unsigned long	ptr;
	int				len;
	char			num[17];
	int				i;

	ptr = (unsigned long)va_arg(*args, void *);
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	len = ft_numlen_ulong(ptr, 16);
	i = len;
	num[i--] = '\0';
	while (ptr)
	{
		num[i--] = "0123456789abcdef"[ptr % 16];
		ptr /= 16;
	}
	return (write(1, num, len) + 2);
}

int	ft_modulo(va_list *args)
{
	(void)*args;
	return (write(1, "%", 1));
}
