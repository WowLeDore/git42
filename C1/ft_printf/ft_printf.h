/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:31 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/16 02:51:25 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>

typedef struct s_format_spec
{
	bool	align_left;
	bool	force_sign;
	bool	space_sign;
	bool	zeros_left;
	bool	alter_form;
	int		width_nmbr;
	bool	precisionb;
	int		precisionv;
	char	specifierf;
}	t_format_spec;

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	put_flg(char flag, va_list arg);

#endif
