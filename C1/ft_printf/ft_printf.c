/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:45:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/09 18:08:39 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *format, ...)
{
	while (*format)
	{
		if (*format != '%')
			write(1, format, 1);
		else if (*(++format) == 'c')
			write(1, format, 1); //NON
		else if (*format == 's')
			write(1, format, 1); //NON
		else if (*format == 'p')
			write(1, format, 1); //NON
		else if (*format == 'd' || *format == 'i')
			write(1, format, 1); //NON
		else if (*format == 'u')
			write(1, format, 1); //NON
		else if (*format == 'x')
			write(1, format, 1); //NON
		else if (*format == 'X')
			write(1, format, 1); //NON
		else if (*format == '%')
			write(1, "%", 1);
		format++;
	}
	return (0);
}
