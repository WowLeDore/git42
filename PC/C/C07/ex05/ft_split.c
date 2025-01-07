/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:18:51 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/27 20:24:12 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

bool	char_in_str(char c, char *str)
{
	while (*str)
	{
		if (c == *(str++))
			return (true);
	}
	return (false);
}

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	word_count(char *str, char *charset)
{
	int		i;
	int		count;
	bool	word;

	i = 0;
	count = 1;
	word = false;
	while (str[i])
	{
		if (char_in_str(str[i++], charset))
			word = false;
		else if (!word)
		{
			count++;
			word = true;
		}
	}
	return (count);
}

char	**alloc_array(char *str, char *charset)
{
	int		i;
	int		count;
	char	**splited;

	i = 0;
	count = 0;
	splited = malloc(word_count(str, charset) * sizeof(char *));
	while (*str)
	{
		if (char_in_str(*(str++), charset))
		{
			if (count)
				splited[i++] = malloc(count * sizeof(char));
			count = 0;
		}
		else if (!count)
			count = 2;
		else
			count++;
	}
	if (count)
		splited[i++] = malloc(count * sizeof(char));
	splited[i] = 0;
	return (splited);
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	char	**splited;

	splited = alloc_array(str, charset);
	i = 0;
	j = 0;
	while (*str)
	{
		if (!char_in_str(*(str++), charset))
		{
			splited[i][j++] = *(str - 1);
			if (char_in_str(*str, charset))
				i++;
		}
		else
		{
			if (j)
				splited[i - 1][j] = '\0';
			j = 0;
		}
	}
	if (j)
		splited[i][j] = '\0';
	return (splited);
}
/*
#include <stdio.h>
int	main(int argc, char *argv[])
{
	int		i;
	char	**splited;

	if (argc != 3)
		return (0);
	i = 0;
	splited = ft_split(argv[1], argv[2]);
	while (splited[i])
		printf("%s\n", splited[i++]);
}
*/
