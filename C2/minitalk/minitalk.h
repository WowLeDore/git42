/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:56:30 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/17 15:32:44 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define BUFFER_SIZE 42

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_message
{
	char	*buffer;
	int		capacity;
	int		i;
}	t_message;

int	verif(char *argv, int len);

#endif
