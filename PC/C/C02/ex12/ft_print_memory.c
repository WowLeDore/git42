/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:55:43 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/24 13:24:56 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_dec_hex_put(unsigned int dec, int bits)
{
	char	*pt_to_hex;
	char	hex[16];
	int		i;

	i = bits - 1;
	while (i >= 0)
	{
		if (dec % 16 < 10)
			hex[i--] = '0' + dec % 16;
		else
			hex[i--] = 'a' + dec % 16 - 10;
		dec /= 16;
	}
	hex[bits] = '\0';
	pt_to_hex = hex;
	while (*pt_to_hex != '\0')
		write(1, pt_to_hex++, 1);
}

void	ft_putstr_non_printable(unsigned char *str, int bits)
{
	int	i;

	i = bits;
	str--;
	while (i > 0)
	{
		if (*++str >= ' ' && *str <= '~')
			write(1, str, 1);
		else
			write(1, ".", 1);
		i--;
	}
}

int	ft_endline(int char_count, int size, int line_count, unsigned char *ptr)
{
	if (char_count == size - 1)
	{
		while (char_count % 16 != 15)
		{
			if (char_count++ % 2 == 1)
				write(1, "   ", 3);
			else
				write(1, "  ", 2);
		}
		if (size % 2 == 1)
			write(1, " ", 1);
	}
	if (char_count % 16 == 15)
		ft_putstr_non_printable(ptr - line_count, line_count);
	if (char_count % 16 == 15)
		write(1, "\n", 1);
	return (char_count + 1);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	char_count;
	unsigned int	line_count;
	unsigned long	dec_addr;
	unsigned char	*pt_to_addr;

	if (addr == 0 || size == 0)
		return (addr);
	char_count = 0;
	pt_to_addr = addr;
	while (char_count < size)
	{
		if (char_count % 16 == 0)
		{
			line_count = 0;
			dec_addr = (unsigned long)pt_to_addr;
			ft_dec_hex_put(dec_addr, 15);
			write(1, ": ", 2);
		}
		ft_dec_hex_put(*(char *)pt_to_addr++, 2);
		if (char_count % 2 == 1)
			write(1, " ", 1);
		char_count = ft_endline(char_count, size, ++line_count, pt_to_addr);
	}
	return (addr);
}
/*
#include <string.h>
int main()
{
	char str1[]={66,111,110,106,111,117,114,32,108,101,115,32,97,109,105,
110,99,104,101,115,9,10,9,99,7,32,101,115,116,32,102,111,117,9,116,111,117,116,
9,99,101,32,113,117,32,111,110,32,112,101,117,116,32,102,97,105,114,101,32,97,
118,101,99,9,10,9,112,114,105,110,116,95,109,101,109,111,114,121,10,10,10,9,
108,111,108,46,108,111,108,10,32,0};
	char str2[] = "Coucou\ntu\xaavas bien ?\xff";
	ft_print_memory(str1,sizeof(str1));
}*/
