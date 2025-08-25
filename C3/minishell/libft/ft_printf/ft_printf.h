/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <pbona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:00:24 by pbona             #+#    #+#             */
/*   Updated: 2025/04/27 10:52:00 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int			ft_printf(const char *format, ...);
int			ft_get_conv(char c);
int			(*ft_get_function(char c))(va_list *);
int			ft_print_conv(char c, va_list *args);

int			ft_c(va_list *args);
int			ft_s(va_list *args);
int			ft_d(va_list *args);
int			ft_i(va_list *args);
int			ft_u(va_list *args);
int			ft_x(va_list *args);
int			ft_xucase(va_list *args);
int			ft_p(va_list *args);
int			ft_modulo(va_list *args);

int			ft_numlen(long n, int base);
int			ft_numlen_ulong(unsigned long n, int base);

#endif
