/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:14:43 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/13 12:37:51 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	to_uint(char *str)
{
	unsigned int	nbr;

	nbr = 0;
	while (str && *str)
		nbr = 10 * nbr + (*(str++) - '0');
	return (nbr);
}

int	is_uint(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
	{
		if (str[len] < '0' || str[len] > '9')
			return (0);
		len++;
	}
	return (len < 10 || (len < 11 && str[0] < '5' && to_uint(str) > 999999999));
}

int	all_uint(int argc, char **argv, t_table *table)
{
	int	i;

	i = 1;
	while (i < argc)
		if (!is_uint(argv[i++]))
			return (0);
	table->number_of_philosophers = to_uint(argv[1]);
	table->time_to_die = to_uint(argv[2]);
	table->time_to_eat = to_uint(argv[3]);
	table->time_to_sleep = to_uint(argv[4]);
	table->dead = 0;
	if (argc == 6)
		table->number_of_times_must_eat = to_uint(argv[5]);
	else
		table->number_of_times_must_eat = 4294967295;
	return (1);
}

t_errors	parse(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6 || !argv)
		return (ARGC);
	if (!all_uint(argc, argv, table))
		return (FORMAT);
	if (table->number_of_philosophers == 0)
		return (PHILO);
	return (OK);
}

int	error(t_errors error)
{
	if (error == OK)
		return (0);
	if (error == ARGC)
		write(2, MSG_ARGC, 37);
	else if (error == FORMAT)
		write(2, MSG_FORMAT, 47);
	else if (error == PHILO)
		write(2, MSG_PHILO, 48);
	else if (error == ALLOC)
		return (1 + 0 * write(2, MSG_ALLOC, 33));
	else if (error == MUTEX)
		return (1 + 0 * write(2, MSG_MUTEX, 46));
	else if (error == THREAD)
		return (1 + 0 * write(2, MSG_THREAD, 47));
	else if (error == TIME)
		return (1 + 0 * write(2, MSG_TIME, 42));
	write(2, "\n", 1);
	write(2, MSG_USAGE1, 40);
	write(2, MSG_USAGE2, 43);
	write(2, MSG_USAGE3, 44);
	write(2, "\n", 1);
	return (1);
}
