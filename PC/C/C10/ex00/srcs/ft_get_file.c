/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:42:25 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/04 21:08:15 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	put_str(char *str, int fd)
{
	write(fd, str, str_len(str));
}

void	read_file(int fd)
{
	int		i;
	char	buff[1];

	i = 1;
	while (i > 0)
	{
		i = read(fd, buff, 1);
		if (i > 0)
			put_str(buff, 1);
	}
}

int	main(int argc, char *argv[])
{
	int	fd;

	if (argc == 1)
		put_str("File name missing.\n", 2);
	if (argc > 2)
		put_str("Too many arguments.\n", 2);
	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		put_str("Cannot read file.\n", 2);
		return (1);
	}
	read_file(fd);
	if (close(fd) < 0)
	{
		put_str("Cannot read file.\n", 2);
		return (1);
	}
	return (0);
}
