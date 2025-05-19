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

void	*live(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	(void) philo;
	write(1, "I am live.\n", 11);
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

t_philo	*born(t_philo *prev, t_fork *left, unsigned int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->dead = 0;
	philo->prev = prev;
	philo->next = NULL;
	philo->left = left;
	philo->right = craft(id);
	if (!philo->right)
	{
		free(philo);
		return (NULL);
	}
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

int	think(t_table *table)
{
	t_philo			*head;
	unsigned int	i;

	head = born(NULL, NULL, 1);
	if (!head)
		return (1);
	table->philos = head;
	i = 2;
	while (i <= table->number_of_philosophers)
	{
		table->philos = born(table->philos, table->philos->right, i);
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
	table->philos = table->philos->next;
	free_all(table);
	return (0);
}

int	error(t_errors error)
{
	if (error == OK)
		return (0);
	if (error == ARGC)
		write(2, MSG_ARGC, 37);
	if (error == FORMAT)
		write(2, MSG_FORMAT, 47);
	if (error == PHILO)
		write(2, MSG_PHILO, 48);
	write(2, "\n", 1);
	write(2, MSG_USAGE1, 40);
	write(2, MSG_USAGE2, 43);
	write(2, MSG_USAGE3, 44);
	write(2, "\n", 1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (error(parse(argc, argv, &table)))
		return (1);
	return (think(&table));
}
