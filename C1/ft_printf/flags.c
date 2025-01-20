/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:16:01 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/14 13:48:29 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_ptr(void *ptr)
{
	printf("%p", ptr);
}

void	put_unb(unsigned int unbr)
{
	printf("%u", unbr);
}

void	put_lhx(unsigned int hex)
{
	printf("%x", hex);
}

void	put_uhx(unsigned int hex)
{
	printf("%X", hex);
}

void	put_flg(char flag, va_list args)
{
	if (flag == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (flag == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	else if (flag == 'p')
		put_ptr(va_arg(args, void *));
	else if (flag == 'd' || flag == 'i')
		ft_putnbr_fd(va_arg(args, int), 1);
	else if (flag == 'u')
		put_unb(va_arg(args, unsigned int));
	else if (flag == 'x')
		put_lhx(va_arg(args, unsigned int));
	else if (flag == 'X')
		put_uhx(va_arg(args, unsigned int));
	else if (flag == '%')
		ft_putchar_fd('%', 1);
}
