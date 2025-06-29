/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:06:20 by pbona             #+#    #+#             */
/*   Updated: 2024/12/01 17:45:25 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len_dest;
	unsigned int	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (size <= len_dest)
	{
		return (size + len_src);
	}
	i = 0;
	while (src [i] != '\0' && len_dest + i < size - 1)
	{
		dest[len_dest + i] = src [i];
		i++;
	}
	dest [len_dest + i] = '\0';
	return (len_dest + len_src);
}
/*#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char *av[])
{
	if (ac == 4)
	{ 
		printf("%i\n", ft_strlcat(av[1], av[2], atoi(av[3])));
		printf("%s\n", av[1]);
	}
	return (0);
}*/
