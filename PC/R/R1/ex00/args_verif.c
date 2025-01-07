/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greandre <greandre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:51:50 by greandre          #+#    #+#             */
/*   Updated: 2024/08/25 17:51:55 by greandre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_01.h"

void	convert_conditions(char *argv[], int conditions[4*N])
{
	int	i;

	i = 0;
	while (i < 4 * N)
	{
		conditions[i] = argv[1][2 * i] - '0';
		i++;
	}
}

bool	verif_args(int argc, char *argv[])
{
	int	i;
	int	size;

	if (argc != 2)
		return (false);
	i = 0;
	size = 0;
	while (argv[1][i])
	{
		i++;
		size++;
	}
	if (size != 4 * N * 2 - 1)
		return (false);
	i = 0;
	while (i < 4 * N * 2 - 1)
	{
		if (argv[1][i] < '1' || argv[1][i] > N + '0')
			return (false);
		i += 2;
		if (i < 4 * N && argv[1][2 * i - 1] != ' ')
			return (false);
	}
	return (true);
}
