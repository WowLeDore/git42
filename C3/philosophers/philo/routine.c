/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:43:01 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/13 13:46:47 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death(t_philo *philo, unsigned int first_fork, unsigned int last_fork)
{
	if (first_fork == last_fork)
		pthread_mutex_unlock(&philo->table->mutexes[first_fork]);
	else
	{
		pthread_mutex_unlock(&philo->table->mutexes[first_fork]);
		pthread_mutex_unlock(&philo->table->mutexes[last_fork]);
	}
	print(philo, "died");
	pthread_mutex_lock(&philo->table->dead_mutex);
	philo->table->dead = 1;
	pthread_mutex_unlock(&philo->table->dead_mutex);
	return (philo);
}

void	*eat(t_philo *philo, unsigned int first_fork, unsigned int last_fork)
{
	pthread_mutex_lock(&philo->table->mutexes[first_fork]);
	print(philo, "has taken a fork");
	if (first_fork == last_fork)
		dodo(philo, philo->table->time_to_die);
	if (timer() >= philo->dead_time)
		return (death(philo, first_fork, first_fork));
	pthread_mutex_lock(&philo->table->mutexes[last_fork]);
	print(philo, "has taken a fork");
	if (timer() >= philo->dead_time)
		return (death(philo, first_fork, last_fork));
	print(philo, "is eating");
	philo->dead_time = timer() + philo->table->time_to_die;
	dodo(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->mutexes[first_fork]);
	pthread_mutex_unlock(&philo->table->mutexes[last_fork]);
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
	first_fork = (philo->id % 2 == 0) * philo->id + (philo->id % 2 == 1)
		* (philo->id + 1) % philo->table->number_of_philosophers;
	last_fork = (philo->id % 2 == 1) * philo->id + (philo->id % 2 == 0)
		* (philo->id + 1) % philo->table->number_of_philosophers;
	while (1)
	{
		print(philo, "is thinking");
		pthread_mutex_lock(&philo->table->dead_mutex);
		dead = philo->table->dead;
		pthread_mutex_unlock(&philo->table->dead_mutex);
		if (dead || philo->meals >= philo->table->number_of_times_must_eat)
			return (p);
		if (philo->id != (philo->meals % philo->table->number_of_philosophers)
			&& philo->table->number_of_philosophers % 2)
			dodo(philo, 10);
		if (eat(philo, first_fork, last_fork))
			return (print(philo, "is thinking"));
	}
	return (NULL);
}
