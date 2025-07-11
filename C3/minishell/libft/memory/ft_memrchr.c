/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:00:05 by pbona             #+#    #+#             */
/*   Updated: 2025/07/07 19:08:58 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		target;

	ptr = s;
	target = (unsigned char) c;
	while (n--)
	{
		if (ptr[n] == target)
			return ((void *)(ptr + n));
	}
	return (NULL);
}
