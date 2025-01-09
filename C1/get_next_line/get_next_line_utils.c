/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:37:51 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/09 16:30:02 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_pos(char *str, char c)
{
	int	pos;

	pos = 0;
	while (str[pos] && str[pos] != c)
		pos++;
	return ((str[pos] != c) * (-1) + (str[pos] == c) * pos);
}

void	*mem_cpy(void *dest, const void *src, size_t n)
{
	char	*dptr;
	char	*sptr;

	dptr = dest;
	sptr = (char *)src;
	while (n-- && (dest || src))
		*(dptr++) = *(sptr++);
	return (dest);
}

size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++ ;
	return (len);
}

char	*add_line(char *dest, char *src, int n)
{
	size_t	dest_size;
	char	*line;

	if (n >= 0)
		n++;
	else
		n = str_len(src);
	dest_size = str_len(dest);
	line = malloc(dest_size + n + 1);
	if (!line)
		return (NULL);
	if (dest)
	{
		mem_cpy(line, dest, dest_size);
		free(dest);
	}
	mem_cpy(line + dest_size, src, n);
	line[dest_size + n] = '\0';
	return (line);
}

int	buff_read(int fd, char (*buffer)[])
{
	int	bytes;

	if (!**buffer)
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (-2);
		if (!bytes)
			return (-3);
		(*buffer)[bytes] = '\0';
	}
	return (get_pos(*buffer, '\n'));
}
