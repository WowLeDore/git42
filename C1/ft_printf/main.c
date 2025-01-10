/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:45:27 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/09 18:50:08 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_printf(const char *str, ...);

int	main(int argc, char **argv)
{
	if (argc != 1 || !argv)
		return (1);
	ft_printf("Character                           : %c\n", 'M');
	ft_printf("String                              : %s\n", "Maxim");
	ft_printf("Pointer                             : %p\n", "");
	ft_printf("Decimal                             : %d\n", 1);
	ft_printf("Integer                             : %i\n", 2);
	ft_printf("Unsigned Integer                    : %u\n", 3);
	ft_printf("Hexadecimal Small                   : %x\n", 43948);
	ft_printf("Hexadecimal Big                     : %X\n", 44527);
	ft_printf("Percentage                          : %%\n");
	ft_printf("5 Field Width Number                : %5d\n", 420);
	ft_printf("Left justified 5 Field Width Number : %-5d\n", 123);
	ft_printf("Zero Padded 5 Field Width Number    : %05d\n", 2);
	ft_printf("String of len 5 with 3 precision    : %.3s\n", "WowLeDore");
	ft_printf("Alternate Form Of Hexadecimal       : %#x\n", 43948);
	ft_printf("Leading Space Before Number         : % d\n", 21);
	ft_printf("Leading Space Before Minus Number   : % d\n", -21);
	ft_printf("Always A Sign Before Decimal        : %+d\n", 42);
	ft_printf("Always A Sign Before Minus Decimal  : %+d\n", -42);
	return (0);
}
