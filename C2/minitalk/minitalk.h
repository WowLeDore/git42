/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:56:30 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/16 01:39:50 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define BITS 8

# include <stdarg.h>
# include <unistd.h>
# include <signal.h>

int	ft_printfd(int fd, const char *format, ...);
int	verif(char *argv, int len);

#endif
