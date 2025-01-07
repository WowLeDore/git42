/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:29:55 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:25:59 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dptr;
	char	*sptr;

	dptr = dest;
	sptr = (char *)src;
	if (dptr > sptr)
	{
		while (n--)
			*(dptr + n) = *(sptr + n);
	}
	else
	{
		while (n-- && (dptr || sptr))
			*(dptr++) = *(sptr++);
	}
	return (dest);
}
