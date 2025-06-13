/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:39:36 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/13 13:39:43 by mguillot         ###   ########.fr       */
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
