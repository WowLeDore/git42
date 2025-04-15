/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:48:58 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/15 18:16:06 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig1(int sig)
{
	(void) sig;
	write(1, "1\n", 2);
}

void	sig2(int sig)
{
	(void) sig;
	write(1, "2\n", 2);
}

int	main(int argc, char **argv)
{
	if (argc != 1 || !argv)
		return (1 + 0 * ft_printfd(2, "Error: Incorrect arguments\nUsage: "
				"./server"));
	ft_printfd(1, "PID: %d\n", getpid());
	signal(SIGUSR1, sig1);
	signal(SIGUSR2, sig2);
	while (1)
		pause();
	return (0);
}
