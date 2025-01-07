/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:33:33 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/01 23:33:35 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main.h"

struct s_number	*ft_parse_file(char *file)
{
	int				i;
	int				j;
	int				len;
	struct s_number	*tab;

	len = ft_len_file(file);
	tab = malloc(sizeof(struct s_number) * (len + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
		ft_parse_line(tab + i++, file, &j);
	tab[i].nb_int = 0;
	return (tab);
}

int	ft_filelen(int fd)
{
	int		size;
	int		bytes;
	char	*buff;

	buff = malloc(sizeof(char) * 2048);
	if (buff == NULL)
		return (0);
	bytes = 1;
	size = 0;
	while (bytes > 0)
	{
		bytes = read(fd, buff, 2048);
		size += bytes;
	}
	free(buff);
	return (size);
}

char	*get_file(char *dict_name)
{
	int		fd;
	char	*str;
	int		file_len;

	fd = open(dict_name, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_putstr("Dict Error\n");
		return (NULL);
	}
	file_len = ft_filelen(fd);
	if (file_len == 0)
		return (NULL);
	str = malloc(sizeof(char) * file_len);
	if (str == NULL)
		return (NULL);
	read(fd, str, file_len);
	if (close(fd) < 0)
	{
		ft_putstr("Dict Error\n");
		return (NULL);
	}
	return (str);
}

void	ft_parse_line(struct s_number *num, char *file, int *i)
{
	int		n;

	n = *i;
	if (file[*i] == '\n')
	{
		num->nb_int = ft_strndup("new_line", 9);
		num->nb_str = ft_strndup("new_line", 9);
		*i += 1;
		return ;
	}
	while (file[*i] >= '0' && file[*i] <= '9')
		*i += 1;
	num->nb_int = ft_strndup(file + n, *i - n + 1);
	while (file[*i] == ' ')
		*i += 1;
	*i += 1;
	while (file[*i] == ' ')
		*i += 1;
	n = *i;
	while (file[*i - 1] && file[*i] != '\n')
		*i += 1;
	*i += 1;
	num->nb_str = ft_strndup(file + n, *i - n);
}

int	ft_len_file(char *file)
{
	int	len;

	len = 0;
	while (*file)
		len += (*(file++) == '\n' && (*(file) != '\n' || *(file - 2) != '\n'));
	return (len);
}
