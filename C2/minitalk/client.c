/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:36:58 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/05 17:34:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_recu = 0;

void	recu_handler(int sig)
{
	(void) sig;
	g_recu = 1;
}

int	str_nbr(char *s, int len, char mode)
{
	int	n;

	if (mode == 'v')
		if (s && *s >= '0' && *s <= '9')
			return (len < 8 && (!*(s + 1) || str_nbr(s + 1, len + 1, 'v')));
	else if (mode == 'c')
	{
		n = 0;
		while (*s >= '0' && *s <= '9')
			n = 10 * n + (*(s++) - '0');
		return (n);
	}
}

void	send_char(pid_t spid, unsigned char c)
{
	int	i;
	int	fail;

	i = 0;
	while (i < 8)
	{
		if ((c >> i++) & 1)
			fail = kill(spid, SIGUSR1);
		else
			fail = kill(spid, SIGUSR2);
		if (fail)
		{
			write(2, "Error: Client failed to send signal\n", 36);
			exit(1);
		}
		while (!g_recu)
			usleep(1);
		g_recu = 0;
	}
}

void	send_all(pid_t spid, char *str)
{
	while (str && *str)
		send_char(spid, *(str++));
	send_char(spid, '\n');
	send_char(spid, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				spid;

	if (argc != 3 || !str_nbr(*(++argv), 0, 'v'))
		if (write(2, "Error: Incorrect arguments\n"
				"Usage: ./client <PID> <message>\n", 59) || 1)
			return (1);
	spid = str_nbr(*(argv++), 0, 'c');
	if (spid < 1 || spid > 4194304)
		if (write(2, "Error: PID number is incorrect\n", 31) || 1)
			return (1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = recu_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		if (write(2, "Error: Client can't handle SIGUSR1 or SIGUSR2\n", 46))
			return (1);
	send_all(spid, *argv);
	return (0);
}
