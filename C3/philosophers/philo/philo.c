/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:56:57 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/13 12:55:59 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

t_errors	free_mutex(t_table *table, unsigned int nb)
{
	int				err;
	unsigned int	i;

	err = 0;
	i = 0;
	if (nb != table->number_of_philosophers)
		err = 1;
	while (i < nb && i < table->number_of_philosophers)
		pthread_mutex_destroy(&table->mutexes[i++]);
	free(table->mutexes);
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->meals_mutex);
	if (err)
		return (MUTEX);
	return (OK);
}

t_errors	free_threads(t_table *table, unsigned int nb)
{
	int				err;
	unsigned int	i;

	err = 0;
	i = 0;
	if (nb != table->number_of_philosophers)
		err = 1;
	while (i < nb && i < table->number_of_philosophers)
		pthread_join(table->threads[i++], NULL);
	free(table->threads);
	if (err)
		return (THREAD);
	return (OK);
}

unsigned long long	timer(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	dodo(t_philo *philo, unsigned long time)
{
	unsigned long	start;
	int				dead;

	start = timer();
	if (!start)
	{
		free_threads(philo->table, philo->table->number_of_philosophers);
		free(philo->table->philos);
		free_mutex(philo->table, philo->table->number_of_philosophers);
		return ;
	}
	while ((timer() - start) < time)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		dead = philo->table->dead;
		pthread_mutex_unlock(&philo->table->dead_mutex);
		if (dead)
			return ;
		usleep(100);
	}
}

void	*print(t_philo *philo, char *str)
{
	int	dead;

	pthread_mutex_lock(&philo->table->dead_mutex);
	dead = philo->table->dead;
	pthread_mutex_unlock(&philo->table->dead_mutex);
	if (dead)
		return (NULL);
	pthread_mutex_lock(&philo->table->print);
	printf("%09llu %u %s\n", timer() - philo->table->timer, philo->id + 1, str);
	pthread_mutex_unlock(&philo->table->print);
	return (philo);
}

void	*handle_death(t_philo *philo, unsigned int f1, unsigned int f2)
{
	if (f1 == f2)
		pthread_mutex_unlock(&philo->table->mutexes[f1]);
	else
	{
		pthread_mutex_unlock(&philo->table->mutexes[f1]);
		pthread_mutex_unlock(&philo->table->mutexes[f2]);
	}
	print(philo, "died");
	pthread_mutex_lock(&philo->table->dead_mutex);
	philo->table->dead = 1;
	pthread_mutex_unlock(&philo->table->dead_mutex);
	return (philo);
}

void	swap(unsigned int *first_fork, unsigned int *last_fork, t_philo *philo)
{
	unsigned int	tmp;

	*first_fork = philo->id;
	*last_fork = (philo->id + 1) % philo->table->number_of_philosophers;
	tmp = *first_fork;
	if (philo->id % 2)
	{
		*first_fork = *last_fork;
		*last_fork = tmp;
	}
}

void	*fork_logic(t_philo *philo, unsigned int ff, unsigned int lf)
{
	print(philo, "is thinking");
	pthread_mutex_lock(&philo->table->mutexes[ff]);
	print(philo, "has taken a fork");
	if (ff == lf)
		dodo(philo, philo->table->time_to_die);
	if (timer() >= philo->dead_time)
		return (handle_death(philo, ff, ff));
	pthread_mutex_lock(&philo->table->mutexes[lf]);
	print(philo, "has taken a fork");
	if (timer() >= philo->dead_time)
		return (handle_death(philo, ff, lf));
	print(philo, "is eating");
	philo->dead_time = timer() + philo->table->time_to_die;
	dodo(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->mutexes[ff]);
	pthread_mutex_unlock(&philo->table->mutexes[lf]);
	pthread_mutex_lock(&philo->table->meals_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->table->meals_mutex);
	print(philo, "is sleeping");
	dodo(philo, philo->table->time_to_sleep);
	if (philo->meals >= philo->table->number_of_times_must_eat)
		return (philo);
	return (NULL);
}

void	*think(void *p)
{
	t_philo			*philo;
	unsigned int	first_fork;
	unsigned int	last_fork;
	int				dead;

	philo = (t_philo *)p;
	swap(&first_fork, &last_fork, philo);
	print(philo, "is thinking");
	while (1)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		dead = philo->table->dead;
		pthread_mutex_unlock(&philo->table->dead_mutex);
		if (dead || philo->meals >= philo->table->number_of_times_must_eat)
			return (p);
		if (philo->id != (philo->meals % philo->table->number_of_philosophers))
			usleep(500);
		if (fork_logic(philo, first_fork, last_fork))
			return (print(philo, "is thinking"));
	}
	return (NULL);
}

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
