/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:48:58 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/16 01:43:42 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sigs(int sig)
{
	static char	c;
	static int	bit;

	if (sig == SIGUSR1)
		c |= 0x01 << bit;
	if (++bit == BITS)
	{
		ft_printfd(1, "%c", c);
		c = 0;
		bit = 0;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 1 || !argv)
		return (1 + 0 * ft_printfd(2, "Error: Incorrect arguments\nUsage: "
				"./server"));
	ft_printfd(1, "PID: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, sigs);
		signal(SIGUSR2, sigs);
		pause();
	}
	return (0);
}
