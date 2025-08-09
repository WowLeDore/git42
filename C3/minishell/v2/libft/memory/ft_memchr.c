/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:00:05 by pbona             #+#    #+#             */
/*   Updated: 2024/11/13 18:45:46 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		target;

	ptr = s;
	target = (unsigned char) c;
	while (n--)
	{
		if (*ptr == target)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
/*
Stp1: Variable initialization
Stp2: Variable affection + Casting target
Stp3: Checking if find target return pointer in finded location
Stp4: Return NULL if not finded
*/
