/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:46:39 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/05 16:24:53 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>

void	handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	msg[BUFFER_SIZE];
	static int				i = 0;
	static int				byte = 0;
	static int				bit = 0;

	(void) context;
	if (sig == SIGUSR1)
		byte |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		msg[i++] = byte;
		if (i >= BUFFER_SIZE || byte == 0)
		{
			write(1, msg, i);
			i = 0;
		}
		bit = 0;
		byte = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	put_pid(int pid)
{
	char	c;

	if (pid > 9)
		put_pid(pid / 10);
	c = pid % 10 + '0';
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 1 || !argv)
		if (write(2, "Error: Incorrect arguments\nUsage: ./server\n", 43) || 1)
			return (1);
	write(1, "Server PID: ", 12);
	put_pid(getpid());
	write(1, "\n", 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		if (write(2, "Error: Server can't handle SIGUSR1 or SIGUSR2\n", 46))
			return (1);
	while (1)
		pause();
	return (0);
}
