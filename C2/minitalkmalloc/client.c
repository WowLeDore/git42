/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:36:58 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/05 20:44:55 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_recu = 0;

void	recu_handler(int sig)
{
	(void) sig;
	g_recu = 1;
}

size_t	verif_convert_len(char mode, char *s, size_t len)
{
	int		n;

	if (mode == 'v' && s && *s >= '0' && *s <= '9')
		return (len < 8 && (!*(++s) || verif_convert_len('v', s, len + 1)));
	else if (mode == 'c')
	{
		n = 0;
		while (*s >= '0' && *s <= '9')
			n = 10 * n + (*(s++) - '0');
		return (n);
	}
	else if (mode == 'l')
	{
		while (s && s[len])
			len++;
		return (len);
	}
	else
		exit(1);
}

void	send_byte(pid_t spid, unsigned char byte)
{
	int	i;
	int	fail;

	i = 0;
	while (i < 8)
	{
		if ((byte >> i++) & 1)
			fail = kill(spid, SIGUSR1);
		else
			fail = kill(spid, SIGUSR2);
		if (fail)
		{
			write(2, "Error: Client failed to send signal\n", 36);
			exit(1);
		}
		while (!g_recu)
			;
		g_recu = 0;
	}
}

void	send_all(pid_t spid, char *str)
{
	unsigned long long	i;
	size_t				len;

	i = 0;
	len = verif_convert_len('l', str, 0);
	while (i < sizeof(size_t))
		send_byte(spid, ((len + 2) >> (8 * i++)) & 0xFF);
	while (str && *str)
		send_byte(spid, *(str++));
	send_byte(spid, '\n');
	send_byte(spid, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				spid;

	if (argc != 3 || !verif_convert_len('v', *(++argv), 0))
		return (write(2, "Error: Incorrect arguments\n"
				"Usage: ./client <PID> <message>\n", 59) * 0 + 1);
	spid = verif_convert_len('c', *(argv++), 0);
	if (spid < 1 || spid > 4194304)
		return (write(2, "Error: PID number is incorrect\n", 31) * 0 + 1);
	if (verif_convert_len('l', *argv, 0) + 2 > MAX_SIZE)
		return (write(2, "Error: Message too long\n", 24) * 0 + 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = recu_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		if (write(2, "Error: Client can't handle signals\n", 46))
			return (1);
	send_all(spid, *argv);
	return (0);
}
