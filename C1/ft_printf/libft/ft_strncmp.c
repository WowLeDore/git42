/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:08:49 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:27:02 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n && *s1 != '\0' && *s1 == *s2)
		n -= 1 + 0 * (*(s1++) * *(s2++));
	return ((n != 0) * ((unsigned char)*s1 - (unsigned char)*s2));
}
