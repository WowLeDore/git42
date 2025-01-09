/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:39:37 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/09 16:28:23 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

int		get_pos(char *str, char c);
void	*mem_cpy(void *dest, const void *src, size_t n);
size_t	str_len(char *str);
char	*add_line(char *dest, char *src, int n);
int		buff_read(int fd, char (*buffer)[]);
char	*get_next_line(int fd);

#endif
