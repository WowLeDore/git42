/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:08:23 by pbona             #+#    #+#             */
/*   Updated: 2024/12/05 16:53:24 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_is_in_charset(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*s2;

	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (i < j && ft_is_in_charset(set, s1[j - 1]) == 1)
			j--;
		while (i < j && ft_is_in_charset(set, s1[i]) == 1)
			i++;
		s2 = malloc((j - i + 1) * sizeof(char));
		if (!s2)
			return (NULL);
		ft_strlcpy(s2, &s1[i], j - i + 1);
	}
	else
		s2 = NULL;
	return (s2);
}
/*#include <stdio.h>
int	main(int ac, char *av[])
{
	if (ac == 3)
	{
		printf("%s\n", ft_strtrim(av[1], av[2]));
		printf("%zu\n", ft_strlen(ft_strtrim(av[1], av[2])));
	}
	return (0);
}*/
