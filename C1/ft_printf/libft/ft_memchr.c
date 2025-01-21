/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:17:11 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/04 20:23:31 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!n)
		return (NULL);
	while (n-- > 1 && *((unsigned char *)s) != (unsigned char)c)
		s++;
	if (s && *((unsigned char *)s) == (unsigned char)c)
		return ((void *)s);
	return (NULL);
}
