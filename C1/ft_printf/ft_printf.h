/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:31 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/20 22:22:08 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "stdarg.h"
# include "stddef.h"
# include "unistd.h"

int	put_str(char *str);
int	put_chr(char c);
int	put_flg(char flag, va_list args);
int	put_lhx(unsigned long long hex);
int	put_nbr(int nbr);
int	put_unb(unsigned int unbr);
int	put_uhx(unsigned int hex);
int	ft_printf(const char *format, ...);

#endif
