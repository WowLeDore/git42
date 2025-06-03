/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:21:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:34 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long	get_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - philo->table->timer);
}

void	dodo(t_philo *philo, unsigned long time)
{
	unsigned long	start;

	start = get_time(philo);
	while ((get_time(philo) - start) < time)
		usleep(20);
}

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%014lu %u %s\n", get_time(philo), philo->id + 1, str);
	pthread_mutex_unlock(&philo->table->print);
}

void	*think(void *p)
{
	t_philo			*philo;
	unsigned int	right;

	philo = (t_philo *)p;
	right = (philo->id + 1) % philo->table->number_of_philosophers;
	print(philo, "is thinking");
	while (1)
	{
		if (philo->id % 2)
			pthread_mutex_lock(&philo->table->mutexes[philo->id]);
		else
			pthread_mutex_lock(&philo->table->mutexes[right]);
		print(philo, "has taken a fork");
		if (philo->id % 2)
			pthread_mutex_lock(&philo->table->mutexes[right]);
		else
			pthread_mutex_lock(&philo->table->mutexes[philo->id]);
		print(philo, "has taken a fork");
		print(philo, "is eating");
		dodo(philo, philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->table->mutexes[right]);
		pthread_mutex_unlock(&philo->table->mutexes[philo->id]);
		print(philo, "is sleeping");
		dodo(philo, philo->table->time_to_sleep);
		print(philo, "is thinking");
	}
	return (p);
}

t_errors	free_mutex(t_table *table, unsigned int nb)
{
	int				err;
	unsigned int	i;

	err = 0;
	if (nb != table->number_of_philosophers)
		err = 1;
	i = 0;
	while (i < nb && i < table->number_of_philosophers)
		pthread_mutex_destroy(&table->mutexes[i++]);
	free(table->mutexes);
	if (err)
		return (MUTEX);
	pthread_mutex_destroy(&table->print);
	return (OK);
}

t_errors	free_threads(t_table *table, unsigned int nb)
{
	int				err;
	unsigned int	i;

	err = 0;
	if (nb != table->number_of_philosophers)
		err = 1;
	i = 0;
	while (i < nb && i < table->number_of_philosophers)
		pthread_join(table->threads[i++], NULL);
	free(table->threads);
	if (err)
		return (THREAD);
	return (OK);
}

t_errors	live(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->timer = get_time(table->philos);
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
		if (pthread_mutex_init(&table->mutexes[i], NULL))
		{
			free_threads(table, 0);
			free(table->philos);
			return (free_mutex(table, i));
		}
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL))
	{
		free_threads(table, 0);
		free(table->philos);
		return (free_mutex(table, table->number_of_philosophers + 1));
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
