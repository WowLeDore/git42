/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:48:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/17 15:16:25 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	str_nbr(char *s)
{
	int		n;

	n = 0;
	while ('0' <= *s && *s <= '9')
		n = 10 * n + (*(s++) - '0');
	return (n);
}

int	verif(char *argv, int len)
{
	if (argv && '0' <= *argv && *argv <= '9')
		return (len < 8 && (!*(argv + 1) || verif(argv + 1, len + 1)));
	return (0);
}

void	send(pid_t pid, unsigned char c)
{
	int	b;

	b = -1;
	while (++b < 8)
		kill(pid, (c >> b & 1) * 10 + (1 - (c >> b & 1)) * 12 + usleep(100));
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	if (argc != 3 || !verif(*(++argv), 0))
		write(2, "Error: Incorrect arguments\n"
			"Usage: ./client <PID> <message>\n", 59);
	if (argc != 3 || !verif(*argv, 0))
		return (1);
	pid = str_nbr(*(argv++));
	if (pid < 1 || pid > 4194304)
		write(2, "Error: PID number is incorrect\n", 31);
	if (pid < 1 || pid > 4194304)
		return (1);
	i = 0;
	while ((*argv)[i])
		send(pid, (unsigned char)(*argv)[i++]);
	send(pid, '\0');
	return (0);
}
