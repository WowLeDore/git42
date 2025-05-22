/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:21:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/22 15:44:58 by mguillot         ###   ########.fr       */
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
		{
			pthread_mutex_lock(&philo->left->lock);
			printf("%014lu %u has taken a fork\n", get_time(philo), philo->id);
			pthread_mutex_lock(&philo->right->lock);
			printf("%014lu %u has taken a fork\n", get_time(philo), philo->id);
		}
		else
		{
			pthread_mutex_lock(&philo->right->lock);
			printf("%014lu %u has taken a fork\n", get_time(philo), philo->id);
			pthread_mutex_lock(&philo->left->lock);
			printf("%014lu %u has taken a fork\n", get_time(philo), philo->id);
		}
		printf("%014lu %u is eating\n", get_time(philo), philo->id);
		philo->meals++;
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->left->lock);
		pthread_mutex_unlock(&philo->right->lock);
		printf("%014lu %u is sleeping\n", get_time(philo), philo->id);
		usleep(philo->table->time_to_sleep * 1000);
		printf("%014lu %u is thinking\n", get_time(philo), philo->id);
	}
}

void	*live(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&philo->table->lock);
		if (philo->table->start)
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

t_fork	*craft(unsigned int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(&fork->lock, NULL))
	{
		free(fork);
		return (NULL);
	}
	fork->id = id;
	return (fork);
}

t_philo	*born(t_philo *prev, t_fork *left, unsigned int id, t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->right = craft(id);
	if (!philo->right)
	{
		free(philo);
		return (NULL);
	}
	philo->left = left;
	philo->next = NULL;
	philo->prev = prev;
	philo->id = id;
	philo->dead = 0;
	philo->meals = 0;
	philo->table = table;
	if (pthread_create(&philo->thread, NULL, live, (void *)philo))
	{
		free(philo->right);
		free(philo);
		return (NULL);
	}
	return (philo);
}

void	free_all(t_table *table)
{
	t_philo			*curr;
	t_philo			*next;

	curr = table->philos;
	while (curr)
	{
		next = curr->next;
		if (curr->right)
		{
			pthread_mutex_destroy(&curr->right->lock);
			free(curr->right);
		}
		pthread_join(curr->thread, NULL);
		free(curr);
		if (!next || next == table->philos)
			return ;
		curr = next;
	}
}

int	init(t_table *table)
{
	t_philo			*head;
	unsigned int	i;

	head = born(NULL, NULL, 1, table);
	if (!head)
		return (1);
	table->philos = head;
	i = 2;
	while (i <= table->number_of_philosophers)
	{
		table->philos = born(table->philos, table->philos->right, i, table);
		if (!table->philos)
		{
			free_all(table);
			return (1);
		}
		table->philos->prev->next = table->philos;
		i++;
	}
	table->philos->next = head;
	head->prev = table->philos;
	head->left = table->philos->right;
	return (0);
}

void	think(t_table *table)
{
	pthread_mutex_lock(&table->lock);
	table->start = 1;
	table->timer = get_time(table->philos);
	pthread_mutex_unlock(&table->lock);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (error(parse(argc, argv, &table)))
		return (1);
	if (pthread_mutex_init(&table.lock, NULL))
		return (1);
	table.start = 0;
	table.timer = 0;
	if (init(&table))
		return (1);
	think(&table);
	free_all(&table);
	return (0);
}
