/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:55:39 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/18 15:07:06 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	src_size;

	src_size = 0;
	while (*src != '\0' && size > 1)
	{
		*dest++ = *src++;
		size--;
		src_size++;
	}
	if (size > 0)
		*dest = '\0';
	while (*src != '\0')
	{
		src++;
		src_size++;
	}
	return (src_size);
}

//#include <stdio.h>
//int main(){char dest[20];
//printf("%u\n",ft_strlcpy(dest,"Hello, World!",sizeof(dest)));
//printf("dest = \"%s\"\n",dest);}
