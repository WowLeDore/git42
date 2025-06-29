/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:58:03 by pbona             #+#    #+#             */
/*   Updated: 2024/11/30 14:58:05 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 0;
	}
	total_size = nmemb * size;
	if (total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
/*
Stp0: Variables total size & ptr
Stp1: Checking if nmemb or size is NULL
Stp2: Global size calculation
Stp3: Checking if overflow with SIZE_MAX
Stp3: Malloc total size pointed by ptr
	Stp3.1: Malloc securization
Stp4: bzero
	Stp4.1: Conversion to char, 1char = 1byte(1 octet)
	Stp4.2: Bytes to zero
*/
