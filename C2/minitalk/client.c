/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:48:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/16 01:43:45 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *nptr)
{
	int		res;
	char	sign;

	while (('\t' <= *nptr && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	sign = *nptr;
	if (sign == '+' || sign == '-')
		nptr++;
	res = 0;
	while ('0' <= *nptr && *nptr <= '9')
		res = 10 * res + (*(nptr++) - '0');
	return (res * (1 - (sign == '-') * 2));
}

int	verif(char *argv, int len)
{
	if (argv && '0' <= *argv && *argv <= '9')
		return (len < 8 && (!*(argv + 1) || verif(argv + 1, len + 1)));
	return (0);
}

void	send(pid_t pid, char c)
{
	int	bit;

	bit = -1;
	while (++bit < BITS)
	{
		if ((c >> bit) % 2)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	if (argc != 3 || !verif(*(++argv), 0))
		return (1 + 0 * ft_printfd(2, "Error: Incorrect arguments\nUsage: "
				"./client <PID> <string>\n"));
	pid = ft_atoi(*(argv++));
	if (pid < 1 || pid > 4194304)
		return (1 + 0 * ft_printfd(2, "Error: PID number is incorrect\n"));
	i = 0;
	while ((*argv)[i])
		send(pid, (*argv)[i++]);
	return (0);
}
