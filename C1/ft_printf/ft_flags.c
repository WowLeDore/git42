/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:16:01 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/20 23:44:13 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	put_chr(char c)
{
	return (write(1, &c, 1));
}

int	put_str(char *str)
{
	return (write(1, str, str_len(str)));
}

int	put_ptr(unsigned long long ptr)
{
	return (write(1, "0x", 2) + put_lhx(ptr));
}

int	put_flg(char flag, va_list args)
{
	if (flag == 'c')
		return (put_chr(va_arg(args, int)));
	if (flag == 's')
		return (put_str(va_arg(args, char *)));
	if (flag == 'p')
		return (put_ptr(va_arg(args, unsigned long long)));
	if (flag == 'd' || flag == 'i')
		return (put_nbr(va_arg(args, int)));
	if (flag == 'u')
		return (put_unb(va_arg(args, unsigned int)));
	if (flag == 'x')
		return (put_lhx(va_arg(args, unsigned int)));
	if (flag == 'X')
		return (put_uhx(va_arg(args, unsigned int)));
	if (flag == '%')
		return (put_chr('%'));
	return (put_chr(flag));
}
