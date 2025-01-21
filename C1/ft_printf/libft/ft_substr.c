/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:50:54 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/04 20:50:18 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	while (i + 1 < siz && src && *src)
		dst[i++] = *(src++);
	if (siz)
		dst[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = ft_strlen(s);
	if (start > i)
		len = 0;
	else if (start + len > i)
		len = i - start;
	if (s)
		sub = malloc(sizeof(char) * (len + 1));
	if (!s || !sub)
		return (NULL);
	ft_strcpy(sub, s + start, len + 1);
	return (sub);
}
