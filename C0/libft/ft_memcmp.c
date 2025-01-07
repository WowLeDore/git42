/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:46:43 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:27:26 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n - 1 && *(unsigned char *)s1 == *(unsigned char *)s2)
		n -= 1 + 0 * *(char *)(s1++) * *(char *)(s2++);
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}
