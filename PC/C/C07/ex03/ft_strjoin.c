/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 05:57:39 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/02 17:52:44 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

char	*str_cat(char *dest, char *src)
{
	char	*str;

	str = dest;
	while (*dest)
		dest++;
	while (*src)
		*(dest++) = *(src++);
	*dest = '\0';
	return (str);
}

char	*str_cpy(char *dest, char *src)
{
	char	*str;

	str = dest;
	while (*src)
		*(dest++) = *(src++);
	*dest = '\0';
	return (str);
}

int	alloc_size(int size, char **strs, char *sep)
{
	int		i;
	int		len;

	i = -1;
	len = -str_len(sep);
	while (++i < size)
		len += str_len(sep) + str_len(strs[i]);
	if (len > 0)
		return (len);
	return (0);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (alloc_size(size, strs, sep) + 1));
	if (size == 0 || str == NULL)
	{
		str = malloc(sizeof(char));
		*str = '\0';
		return (str);
	}
	i = -1;
	while (++i < size)
	{
		if (i == 0)
			str = str_cpy(str, strs[i]);
		else
			str = str_cat(str, strs[i]);
		if (i + 1 < size)
			str = str_cat(str, sep);
	}
	return (str);
}
/*
#include <stdio.h>
int main(int argc, char *argv[])
{
	char *sep;
	char *res;
	if (argc < 3)
		return (0);
	sep = *(++argv);
	res = ft_strjoin(argc - 2, ++argv, sep);
	printf("%s", res);
	free(res);
}
*/
