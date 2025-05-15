/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:14:43 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/14 19:05:29 by mguillot         ###   ########.fr       */
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

int	all_uint(int argc, char **argv, t_philo *philo)
{
	int	i;

	i = 1;
	while (i < argc)
		if (!is_uint(argv[i++]))
			return (0);
	philo->number_of_philosophers = to_uint(argv[1]);
	philo->time_to_die = to_uint(argv[2]);
	philo->time_to_eat = to_uint(argv[3]);
	philo->time_to_sleep = to_uint(argv[4]);
	if (argc == 6)
		philo->number_of_times_each_philosopher_must_eat = to_uint(argv[5]);
	else
		philo->number_of_times_each_philosopher_must_eat = 0;
	return (1);
}

t_errors	parse(int argc, char **argv, t_philo *philo)
{
	if (argc < 5 || argc > 6 || !argv)
		return (ARGC);
	if (!all_uint(argc, argv, philo))
		return (FORMAT);
	if (philo->number_of_philosophers == 0)
		return (PHILO);
	return (OK);
}
