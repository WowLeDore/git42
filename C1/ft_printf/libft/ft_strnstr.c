/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:57:58 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:27:40 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, const char *little, size_t len)
{
	size_t	i;

	while (len-- && *big)
	{
		i = 0;
		while (i <= len && little[i] && big[i] == little[i])
			i++;
		if (big++ && !little[i])
			return (big - 1);
	}
	if (*little)
		return (NULL);
	return (big);
}
