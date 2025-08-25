/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:00:46 by pbona             #+#    #+#             */
/*   Updated: 2024/11/29 19:09:18 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = dest;
	s = src;
	if (s < d && d < s + n)
	{
		s += n -1;
		d += n -1;
		while (n--)
			*d-- = *s--;
	}
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}
/* 
Stp1: Conversion to unsigned char
Stp2: Checking if forward overlap
	Stp2.1: Move of d & c in end of copy zone
	Stp2.2: Copy from end
Stp3: No overlap, or backoverlap, copy from start
Stp4: Return dest
*/
