/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:56:57 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/13 13:43:09 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

t_errors	live(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->timer = timer();
	if (!table->timer)
	{
		free(table->threads);
		free(table->philos);
		free_mutex(table, table->number_of_philosophers);
		return (TIME);
	}
	while (i < table->number_of_philosophers)
	{
		if (pthread_create(&table->threads[i], NULL, think, &table->philos[i]))
		{
			free_mutex(table, table->number_of_philosophers);
			free(table->philos);
			return (free_threads(table, i));
		}
		i++;
	}
	return (OK);
}

t_errors	sit(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philos[i].table = table;
		table->philos[i].id = i;
		table->philos[i].dead_time = timer() + table->time_to_die;
		table->philos[i].meals = 0;
		if (pthread_mutex_init(&table->mutexes[i++], NULL))
		{
			free_threads(table, 0);
			free(table->philos);
			return (free_mutex(table, i - 1));
		}
	}
	if (pthread_mutex_init(&table->print, NULL)
		|| pthread_mutex_init(&table->dead_mutex, NULL)
		|| pthread_mutex_init(&table->meals_mutex, NULL))
	{
		free_threads(table, 0);
		free(table->philos);
		return (free_mutex(table, table->number_of_philosophers));
	}
	return (live(table));
}

t_errors	alloc(t_table *table)
{
	unsigned int	nb;

	nb = table->number_of_philosophers;
	table->threads = malloc(sizeof(pthread_t) * nb);
	if (!table->threads)
		return (ALLOC);
	table->mutexes = malloc(sizeof(pthread_mutex_t) * nb);
	if (!table->mutexes)
	{
		free(table->threads);
		return (ALLOC);
	}
	table->philos = malloc(sizeof(t_philo) * nb);
	if (!table->philos)
	{
		free(table->threads);
		free(table->mutexes);
		return (ALLOC);
	}
	return (sit(table));
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (error(parse(argc, argv, &table)))
		return (1);
	if (error(alloc(&table)))
		return (1);
	free_threads(&table, table.number_of_philosophers);
	free(table.philos);
	free_mutex(&table, table.number_of_philosophers);
	return (0);
}
