/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:03:11 by pbona             #+#    #+#             */
/*   Updated: 2025/06/29 02:10:36 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c)
{
	int	nb_words;

	nb_words = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && c == *str)
			str++;
		if (*str != '\0')
			nb_words++;
		while (*str != '\0' && c != *str)
			str++;
	}
	return (nb_words);
}

static char	*ft_strndup(const char *src, int n)
{
	char	*dest;
	int		i;

	if (src == NULL)
		return (NULL);
	dest = malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest [i] = src [i];
		i++;
	}
	dest [i] = '\0';
	return (dest);
}

static void	*ft_free_split(char **split, int i)
{
	while (i >= 0)
		free(split[i--]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	t_split_v	sv;

	sv.split = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (sv.split == NULL)
		return (NULL);
	sv.index = 0;
	while (s && *s)
	{
		while (*s && *s == c)
			s++;
		sv.ptr = ft_strchr(s, c);
		if (!sv.ptr)
			sv.len = ft_strlen(s);
		else
			sv.len = sv.ptr - s;
		if (!sv.len)
			break ;
		sv.split[sv.index++] = ft_strndup(s, sv.len);
		if (!sv.split[sv.index - 1])
			return (ft_free_split(sv.split, sv.index - 2));
		s = sv.ptr;
	}
	sv.split[sv.index] = 0;
	return (sv.split);
}
/*#include <stdio.h>

int	main(int ac, char *av[])
{
	int	i;
	char	**split;

	if (ac == 3)
	{
		split = ft_split(av[1], av[2][0]);
		i = 0;
		while (split [i] != 0)
		{
			printf("word %d : %s\n", i, split [i]);
			free(split[i]);	
			i++;
		}
		free (split);
	}
	return (0);

Stp 0: Variable declaratiom
Stp1: malloc size counted words
Stp2: securization malloc
Stp3: index to 0
Stp4: whiole s not 0 & *s not null
Stp5: skipping charset
Stp6: strchr to take a pointer to the next charset
Stp7: if strchr si nul, char not founded: or the last word or the end of 
the string
Stp7.1: len = strlen(s) size of the string
Stp7.2: len = soze of the word ptr - s
Stp8: if !len, not the last word but not the last char of string, 
break to continue
Stp9: else strndup
Stp10: Checking if strndup success
Stp11 : update s value  with ptr to countinue in scale ptr to s, s to ptr
Stp12: if while finished, set last to zero;
}*/
