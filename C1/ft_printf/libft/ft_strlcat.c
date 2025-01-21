/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:19:17 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/04 20:06:05 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	retval;
	size_t	i;
	int		null_term;

	null_term = (siz && ft_memchr((const void *)dst, '\0', siz - 1));
	retval = ft_strlen(src) + siz;
	if (siz > ft_strlen(dst))
		retval = ft_strlen(src) + ft_strlen(dst);
	i = 0;
	while (i + 1 < siz && dst[i])
		i++;
	while (i + 1 < siz && src && *src)
		dst[i++] = *(src++);
	if (null_term)
		dst[i] = '\0';
	return (retval);
}
