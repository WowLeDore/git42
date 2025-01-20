/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:45:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/16 10:52:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format_spec	extract_specifier(char *str)
{
	int				index;
	t_format_spec	*specifier;

	index = 0;
	if (str[index++] != '%')
		return (0);
	if (str[])
}

int	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			put_flg(*(++format), args);
		else
			ft_printf("%c", *format);
		format++;
	}
	return (0);
}
