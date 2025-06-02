/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:58 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/02 17:43:41 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long	get_time(t_philo *philo)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - philo->table->timer);
}

void	life(t_philo *philo)
{
	while (1)
	{
		if (philo->id % 2)
			pthread_mutex_lock(&philo->prev->fork);
		else
			pthread_mutex_lock(&philo->fork);
		printf("%014lu %u has taken a fork\n", get_time(philo), philo->id);
		if (philo->id % 2)
			pthread_mutex_lock(&philo->fork);
		else
			pthread_mutex_lock(&philo->prev->fork);
		printf("%014lu %u has taken a fork\n", get_time(philo), philo->id);
		printf("%014lu %u is eating\n", get_time(philo), philo->id);
		philo->meals++;
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->prev->fork);
		printf("%014lu %u is sleeping\n", get_time(philo), philo->id);
		usleep(philo->table->time_to_sleep * 1000);
		printf("%014lu %u is thinking\n", get_time(philo), philo->id);
	}
}

void	*live(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->table->lock);
	philo->table->ready++;
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_unlock(&philo->table->lock);
	while (1)
	{
		pthread_mutex_lock(&philo->table->lock);
		if (philo->table->timer)
		{
			pthread_mutex_unlock(&philo->table->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->lock);
	}
	printf("%014lu %u is thinking\n", get_time(philo), philo->id);
	life(philo);
	return (NULL);
}

int	think(t_table *table)
{
	t_philo			*curr;
	t_philo			*next;
	unsigned int	i;

	i = 1;
	curr = table->philos;
	while (i <= table->number_of_philosophers)
	{
		if (pthread_create(&curr->thread, NULL, live, (void *)curr))
			return (free_all(table, i));
		next = curr->next;
		curr = next;
		i++;
	}
	while (!table->timer)
	{
		pthread_mutex_lock(&table->lock);
		if (table->ready == table->number_of_philosophers)
			table->timer = get_time(table->philos);
		pthread_mutex_unlock(&table->lock);
	}
	return (0);
}
