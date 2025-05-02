/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:48:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/01 21:47:23 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send(pid_t pid, unsigned char c)
{
	int	bit;
	int	fail;

	bit = -1;
	while (++bit < 8)
	{
		usleep(100);
		if (c >> bit & 0x01)
			fail = kill(pid, SIGUSR2);
		else
			fail = kill(pid, SIGUSR1);
		if (fail)
			if (write(2, "Error: Client failed to send signal\n", 36) || 1)
				exit(1);
	}
}

void	send_len(pid_t spid, char *str)
{
	size_t	len;
	int		count;
	int		digits[4];

	len = 0;
	while (str[len++])
		;
	count = 0;
	while (len && count < 4)
	{
		digits[count++] = (len % 127) + 1;
		len /= 127;
	}
	while (count--)
		send(spid, digits[count]);
	send(spid, 0);
}

void	send_all(pid_t cpid, pid_t spid, char *str)
{
	int		count;
	int		digits[4];

	count = 0;
	while (cpid && count < 4)
	{
		digits[count++] = (cpid % 127) + 1;
		cpid /= 127;
	}
	while (count--)
		send(spid, digits[count]);
	send(spid, 0);
	send_len(spid, str);
	while (str && *str)
		send(spid, *(str++));
	send(spid, '\n');
	send(spid, 0);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		if (write(2, "Error: Server did not receive message correctly\n", 48))
			exit(1);
	write(1, "Success: Server received message correctly\n", 43);
	exit(0);
}

int	main(int argc, char **argv)
{
	pid_t				cpid;
	pid_t				spid;
	struct sigaction	sa;

	if (argc != 3 || !verif(*(++argv), 0))
		if (write(2, "Error: Incorrect arguments\n"
				"Usage: ./client <PID> <message>\n", 59) || 1)
			return (1);
	spid = str_nbr(*(argv++));
	if (spid < 1 || spid > 4194304)
		if (write(2, "Error: PID number is incorrect\n", 31) || 1)
			return (1);
	cpid = getpid();
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		if (write(2, "Error: Client can't handle SIGUSR1 or SIGUSR2\n", 46))
			return (1);
	send_all(cpid, spid, *argv);
	while (1)
		pause();
	return (0);
}
