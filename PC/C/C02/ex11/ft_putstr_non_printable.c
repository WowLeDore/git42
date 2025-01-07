/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:53:26 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/21 22:51:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_char_is_printable(char c)
{
	if (c < 32 || c == 127)
		return (0);
	return (1);
}

void	ft_putdec_hex(int dec)
{
	char	hex;

	if (dec < 10)
	{
		hex = '0' + dec;
		write(1, &hex, 1);
	}
	else if (dec < 16)
	{
		hex = 'a' + dec - 10;
		write(1, &hex, 1);
	}
	else
	{
		ft_putdec_hex(dec / 16);
		ft_putdec_hex(dec % 16);
	}
}

void	ft_putchar_hex(unsigned char c)
{
	int		dec;

	dec = c;
	write(1, "\\", 1);
	if (dec < 16)
		write(1, "0", 1);
	ft_putdec_hex(dec);
}

void	ft_putstr_non_printable(char *str)
{
	while (*str != '\0')
	{
		if (ft_char_is_printable(*str))
			write(1, str, 1);
		else
			ft_putchar_hex(*str);
		str++;
	}
}
/*int main()
{
	char    str[] = "Coucou\ntu\xaavas bien ?";
	ft_putstr_non_printable(str);
}*/
