/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:23:04 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:25:48 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dptr;
	char	*sptr;

	dptr = dest;
	sptr = (char *)src;
	while (n-- && (dest || src))
		*(dptr++) = *(sptr++);
	return (dest);
}
