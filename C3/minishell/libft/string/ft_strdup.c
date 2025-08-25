/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:05:35 by pbona             #+#    #+#             */
/*   Updated: 2024/12/01 15:54:41 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src [i] != '\0')
	{
		dest [i] = src [i];
		i++;
	}
	dest [i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (dest == NULL)
	{
		return (NULL);
	}
	return (ft_strcpy(dest, src));
}
/*#include <stdio.h>
#include <string.h>

int	main(int agc, char *agv[])
{
	char *dest;

	if (agc == 2) 
	{
		dest = ft_strdup(agv[1]);
		printf("%p\n", agv[1]);
		printf("%p\n", dest);
		printf("%s\n", agv[1]);
		printf("%s\n", dest);
		free(dest);
	}
	return (0);
}*/
