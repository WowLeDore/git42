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

#include <stdio.h>

int	ft_printf(const char *str, ...);

int	main(int argc, char **argv)
{
	if (argc != 1 || !argv)
		return (1);
	printf("Character                           : %c\n", 'M');
	printf("String                              : %s\n", "Maxim");
	printf("Pointer                             : %p\n", "");
	printf("Decimal                             : %d\n", 1);
	printf("Integer                             : %i\n", 2);
	printf("Unsigned Integer                    : %u\n", 3);
	printf("Hexadecimal Small                   : %x\n", 43948);
	printf("Hexadecimal Big                     : %X\n", 44527);
	printf("Percentage                          : %%\n");
	printf("5 Field Width Number                : %5d\n", 420);
	printf("Left justified 5 Field Width Number : %-5d\n", 123);
	printf("Zero Padded 5 Field Width Number    : %05d\n", 1010);
	printf("String of len 5 with 3 precision    : %.3s\n", "WowLeDore");
	printf("Alternate Form Of Hexadecimal       : %#x\n", 43948);
	printf("Leading Space Before Number         : % d\n", 21);
	printf("Always A Sign Before Decimal        : %+d\n", 42);
	return (0);
}
