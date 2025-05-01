/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:12:00 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/01 17:50:11 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_global	g_g = {0, 0};

void	cpid_len_handle(int *i, pid_t *cpid, size_t *len, char **msg)
{
	if (*i == -2)
	{
		if (g_g.byte)
			*cpid = *cpid * 127 + (g_g.byte - 1);
		else
			*i = -1;
	}
	else if (*i == -1)
	{
		if (g_g.byte)
			*len = *len * 127 + (g_g.byte - 1);
		else
		{
			*msg = malloc(*len + 1);
			if (!*msg)
				if (kill(*cpid, SIGUSR1) || 1)
					exit(1);
			*i = 0;
		}
	}
}

void	handler(int sig)
{
	static pid_t	cpid = 0;
	static size_t	len = 0;
	static char		*msg = 0;
	static int		i = -2;

	if (sig == SIGUSR2)
		g_g.byte |= (1 << g_g.bit);
	g_g.bit++;
	if (g_g.bit == 8)
	{
		if (i == -2 || i == -1)
			cpid_len_handle(&i, &cpid, &len, &msg);
		else if (i > -1)
		{
			if (!g_g.byte)
			{
				msg[i] = 0;
				write(1, msg, i);
				kill(cpid, SIGUSR2);
				free(msg);
				len = 0;
				cpid = 0;
				msg = 0;
				i = -2;
			}
			else
			{
				if (msg)
					msg[i++] = g_g.byte;
			}
		}
		g_g.bit = 0;
		g_g.byte = 0;
	}
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
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		if (write(2, "Error: Server can't handle SIGUSR1 or SIGUSR2\n", 46))
			return (1);
	write(1, "Server PID: ", 12);
	put_pid(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
