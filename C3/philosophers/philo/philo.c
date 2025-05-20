/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:21:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/19 13:39:39 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	timestamp_ms(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000) - philo->table->timer);
}

void	odd_life(t_philo *philo)
{
	(void) philo;
}

void	even_life(t_philo *philo)
{
	while (1)
	{
		if (philo->id % 2)
		{
			pthread_mutex_lock(&philo->left->lock);
			printf("%lu %u has taken a fork\n", timestamp_ms(philo), philo->id);
			pthread_mutex_lock(&philo->right->lock);
			printf("%lu %u has taken a fork\n", timestamp_ms(philo), philo->id);
		}
		else
		{
			pthread_mutex_lock(&philo->right->lock);
			printf("%lu %u has taken a fork\n", timestamp_ms(philo), philo->id);
			pthread_mutex_lock(&philo->left->lock);
			printf("%lu %u has taken a fork\n", timestamp_ms(philo), philo->id);
		}
		printf("%lu %u is eating\n", timestamp_ms(philo), philo->id);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->left->lock);
		pthread_mutex_unlock(&philo->right->lock);
		printf("%lu %u is sleeping\n", timestamp_ms(philo), philo->id);
		usleep(philo->table->time_to_sleep * 1000);
		printf("%lu %u is thinking\n", timestamp_ms(philo), philo->id);
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
	if (philo->table->number_of_philosophers % 2)
		even_life(philo);
	else
		even_life(philo);
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
	philo->table = table;
	philo->id = id;
	philo->dead = 0;
	philo->prev = prev;
	philo->next = NULL;
	philo->left = left;
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
	table->timer = timestamp_ms(table->philos);
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
