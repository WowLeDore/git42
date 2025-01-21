/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:23:51 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:52:07 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*trimmed;

	if (!s1)
		return (NULL);
	while (s1 && *s1 && set && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i > 0 && set && ft_strchr(set, s1[i - 1]))
		i--;
	trimmed = malloc(sizeof(char) * i + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1, i + 1);
	return (trimmed);
}
