/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:39:24 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/31 21:04:02 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	n_option(char *str)
{
	if (!str || *(str++) != '-' || *(str++) != 'n')
		return (0);
	while (*str && *str == 'n')
		str++;
	return (!*str);
}

int	echo(int argc, char **argv)
{
	int	newline;
	int	i;

	i = 1;
	while (i < argc && n_option(argv[i]))
		i++;
	newline = i == 1;
	if (i < argc)
		if (write(1, argv[i], ft_strlen(argv[i])) < 0)
			return (1);
	while (++i < argc)
		if (write(1, " ", 1) < 0 || write(1, argv[i], ft_strlen(argv[i])) < 0)
			return (1);
	if (newline)
		if (write(1, "\n", 1) < 0)
			return (1);
	return (0);
}
