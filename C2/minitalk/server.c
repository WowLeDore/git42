/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:12:00 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/28 14:34:17 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_global
{
	int	bit;
	int	byte;
}	t_global;

static t_global	g_g = {0, 0};

void	handler(int sig)
{
	static pid_t	cpid = 0;
	static size_t	len = 0;
	static size_t	idx = 0;
	static char		*msg = 0;
	static int		stage = 0;

	if (sig == SIGUSR2)
		g_g.byte |= (1 << g_g.bit);
	g_g.bit++;
	if (g_g.bit == 8)
	{
		if (stage == 0)
		{
			if (g_g.byte)
				cpid = cpid * 127 + (g_g.byte - 1);
			else
				stage = 1;
		}
		else if (stage == 1)
		{
			if (g_g.byte)
				len = len * 127 + (g_g.byte - 1);
			else
			{
				msg = malloc(len + 1);
				if (!msg)
				{
					if (cpid)
						kill(cpid, SIGUSR1);
					exit(1);
				}
				idx = 0;
				stage = 2;
			}
		}
		else if (stage == 2)
		{
			if (g_g.byte == '\n')
			{
				msg[idx] = 0;
				write(1, msg, idx);
				write(1, "\n", 1);
				free(msg);
				msg = 0;
				stage = 0;
				if (cpid)
					kill(cpid, SIGUSR2);
			}
			else
			{
				if (msg)
					msg[idx++] = g_g.byte;
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
