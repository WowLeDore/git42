/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:07:50 by pbona             #+#    #+#             */
/*   Updated: 2024/11/29 17:38:45 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (*big && len >= little_len)
	{
		if (ft_strncmp((char *)big, (char *)little, little_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
/*
Stp1: little_len
Stp2: Check if little isempty
Stp3: browse big and check that the remaining size to compare is long enough
Stp4: Checking whit strncmp ifexact correspondance in beetween big and little
Stp5: return NULL if little not finded
*/
