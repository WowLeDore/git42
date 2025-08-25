/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:06:09 by pbona             #+#    #+#             */
/*   Updated: 2024/11/29 17:39:40 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char const *src)
{
	int	size_dest;
	int	i;

	size_dest = ft_strlen(dest);
	i = 0;
	while (src [i] != '\0')
	{
		dest[size_dest + i] = src [i];
		i++;
	}
	dest [size_dest + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	*str = '\0';
	ft_strcat(str, s1);
	ft_strcat(str, s2);
	return (str);
}
/*#include <stdio.h>

int	main(int ac, char *av[])
{
	char	*str;

	if (ac == 3)
	{
		str = ft_strjoin(av[1], av[2]);
		printf ("%s", str);
		free (str);
	}
	return (0);
}*/
