/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:47:55 by pbona             #+#    #+#             */
/*   Updated: 2025/04/24 16:47:56 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extract_line(char *buffer)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	tmp = malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		tmp[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	return (tmp);
}

static char	*ft_update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	tmp = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!tmp)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		tmp[j++] = buffer[i++];
	tmp[j] = '\0';
	free(buffer);
	return (tmp);
}

static char	*ft_init_buffer(char *buffer)
{
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	return (buffer);
}

static char	*ft_read_line(int fd, char *buffer)
{
	char	*reading;
	char	*temp;
	int		bytes_read;

	buffer = ft_init_buffer(buffer);
	if (!buffer)
		return (NULL);
	reading = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!reading)
		return (free(buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, reading, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(reading), NULL);
		reading[bytes_read] = '\0';
		temp = ft_strjoin(buffer, reading);
		if (!temp)
			return (free(buffer), free(reading), NULL);
		free(buffer);
		buffer = temp;
	}
	return (free(reading), buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buffer[fd] = ft_read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_extract_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_update_buffer(buffer[fd]);
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char *av[])
{
	int	fd1;
	int	fd2;
	char	*line;

	if (ac > 2)
	{
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[2], O_RDONLY);
		line = get_next_line(fd1);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd1);
		}
		line = get_next_line(fd2);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd2);
		}
		close(fd1);
		close(fd2);
	}
	return (0);
}*/
