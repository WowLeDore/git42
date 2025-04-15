/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:48:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/15 18:15:18 by mguillot         ###   ########.fr       */
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

int	gs(char c, int i)
{
	if (!i)
		return (c % 2 + 1);
	return ((c != 0) * gs(c / 2, i - 1));
}

int	verif(char *argv, int len)
{
	if (argv && '0' <= *argv && *argv <= '9')
		return (len < 8 && (!*(argv + 1) || verif(argv + 1, len + 1)));
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	if (argc != 3 || !verif(*(++argv), 0))
		return (1 + 0 * ft_printfd(2, "Error: Incorrect arguments\nUsage: "
				"./client <PID> <string>\n"));
	if (ft_atoi(*argv) < 1 || ft_atoi(*argv) > 4194304)
		return (1 + 0 * ft_printfd(2, "Error: PID number is incorrect\n"));
	pid = ft_atoi(*(argv++));
	//while (argv && *argv)
	//{
	ft_printfd(1, "%c\n", **argv);
	i = -1;
	while (gs(**argv, ++i))
		kill(pid,
			(2 - gs(**argv, i)) * SIGUSR1 + (gs(**argv, i) - 1) * SIGUSR2);
	//}
	return (0);
}
