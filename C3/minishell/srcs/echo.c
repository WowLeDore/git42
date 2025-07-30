/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:39:24 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/30 23:42:56 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	n_option(int argc, char **argv)
{
	return (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n' && !argv[1][2]);
}

int	echo(int argc, char **argv)
{
	int	i;

	while (n_option(argc, argv) && n_option(argc - 1, argv + 1))
	{
		argc--;
		argv++;
	}
	i = n_option(argc, argv);
	while (++i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(" ");
	}
	if (!n_option(argc, argv))
		printf("\n");
	return (0);
}
