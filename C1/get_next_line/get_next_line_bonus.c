/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:37:51 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/09 16:30:02 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	int			line_pos;

	next_line = NULL;
	while (1)
	{
		line_pos = buff_read(fd, &buffer);
		if (line_pos == -2)
			free(next_line);
		if (line_pos == -2)
			return (NULL);
		if (line_pos == -3)
			break ;
		next_line = add_line(next_line, buffer, line_pos);
		if (!next_line)
			return (NULL);
		if (line_pos >= 0)
			mem_cpy(buffer, buffer + line_pos + 1, str_len(buffer) - line_pos);
		else
			buffer[0] = '\0';
		if (line_pos >= 0)
			break ;
	}
	return (next_line);
}
