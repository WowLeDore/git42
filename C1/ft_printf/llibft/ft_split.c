/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:48:34 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:28:39 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_arrlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len += ((*s == c || *s == '\0') && *(s - 1) != c);
	return (len);
}

static size_t	ft_wordlen(char const **s, char c)
{
	size_t	len;

	while (**s == c)
		(*s)++;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	return (len);
}

static char	**ft_freeall(char **s, size_t len)
{
	while (len)
		free(s[--len]);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	arr_i;
	size_t	word_i;
	size_t	wordlen;
	char	**splitted;

	arr_i = 0;
	if (s)
		splitted = malloc(sizeof(char *) * (ft_arrlen(s, c) + 1));
	if (!s || !splitted)
		return (NULL);
	while (ft_arrlen(s, c))
	{
		wordlen = ft_wordlen(&s, c);
		splitted[arr_i] = malloc(sizeof(char) * (wordlen + 1));
		if (!splitted[arr_i])
			return (ft_freeall(splitted, arr_i));
		word_i = -1;
		while (++word_i < wordlen)
			splitted[arr_i][word_i] = s[word_i];
		splitted[arr_i++][word_i] = '\0';
		s += wordlen;
	}
	splitted[arr_i] = NULL;
	return (splitted);
}
