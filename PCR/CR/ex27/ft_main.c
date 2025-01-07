/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:35:05 by mguillot          #+#    #+#             */
/*   Updated: 2024/11/04 19:20:02 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void	ft_puterror(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		bytes;
	char	buffer[64];

	if (argc < 2)
		ft_puterror("File name missing.\n");
	if (argc > 2)
		ft_puterror("Too many arguments.\n");
	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_puterror("Cannot read file.\n");
	if (fd == -1)
		return (1);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, sizeof(buffer));
		write(1, buffer, bytes);
	}
	close(fd);
	return (0);
}
