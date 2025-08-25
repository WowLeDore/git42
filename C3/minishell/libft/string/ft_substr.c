/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:08:41 by pbona             #+#    #+#             */
/*   Updated: 2024/12/01 22:35:18 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*d;
	size_t			size_d;
	unsigned int	i;
	size_t			j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) > start + len)
		size_d = len;
	else
		size_d = ft_strlen(s) - start;
	d = malloc((size_d + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (s [i] != '\0' && j < size_d)
	{
		d [j++] = s [i++];
	}
	d [j] = '\0';
	return (d);
}
