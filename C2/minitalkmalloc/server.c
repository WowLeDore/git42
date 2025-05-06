/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:46:39 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/06 03:24:31 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	put_message(unsigned char **msg, size_t i)
{
	write(1, "\n", 1);
	write(1, "==================== +=============+ ====================\n", 58);
	write(1, "==================== |BEGIN MESSAGE| ====================\n", 58);
	write(1, "==================== +=============+ ====================\n", 58);
	write(1, *msg, i);
	write(1, "====================  +===========+  ====================\n", 58);
	write(1, "====================  |END MESSAGE|  ====================\n", 58);
	write(1, "====================  +===========+  ====================\n", 58);
	write(1, "\n", 1);
	free(*msg);
	*msg = NULL;
}

void	put_pid(int pid)
{
	char	c;

	if (pid > 9)
		put_pid(pid / 10);
	c = pid % 10 + '0';
	write(1, &c, 1);
}

int	handle_byte(int byte)
{
	static unsigned char	*msg = NULL;
	static size_t			i = 0;
	static size_t			len = 0;
	static int				len_byte = 0;

	if (len_byte < (int) sizeof(size_t))
		len |= ((size_t) byte) << (8 * len_byte++);
	else
	{
		if (len > MAX_SIZE)
			return (write(2, "Error: Message too long.\n", 25) * 0 + 1);
		if (!msg)
			msg = malloc(len);
		if (!msg)
			return (write(2, "Error: Malloc failed\n", 21) * 0 + 1);
		msg[i++] = byte;
		if (i == len)
		{
			put_message(&msg, i);
			i = 0;
			len = 0;
			len_byte = 0;
		}
	}
	return (0);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int	byte = 0;
	static int	bit = 0;

	(void) context;
	if (sig == SIGUSR1)
		byte |= (1 << bit++);
	else if (sig == SIGUSR2)
		bit++;
	if (bit == 8)
	{
		if (handle_byte(byte))
		{
			kill(info->si_pid, SIGUSR2);
			exit(1);
		}
		byte = 0;
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 1 || !argv)
		return (write(2, "Error: Incorrect arguments\n"
				"Usage: ./server\n", 43) * 0 + 1);
	write(1, "Server PID: ", 12);
	put_pid(getpid());
	write(1, "\n", 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "Error: Server can't handle signals\n", 35) * 0 + 1);
	while (1)
		pause();
	return (0);
}
