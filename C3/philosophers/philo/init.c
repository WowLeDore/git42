/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:20:09 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/27 14:45:29 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_table *table, unsigned int thread)
{
	t_philo			*curr;
	t_philo			*next;
	unsigned int	i;

	i = 1;
	curr = table->philos;
	while (i <= table->number_of_philosophers)
	{
		if (!pthread_mutex_lock(&curr->fork)
			&& !pthread_mutex_unlock(&curr->fork))
			pthread_mutex_destroy(&curr->fork);
		if (i <= thread)
			pthread_join(curr->thread, NULL);
		next = curr->next;
		free(curr);
		curr = next;
		i++;
	}
	return (1);
}

t_philo	*born(t_philo *prev, unsigned int id, t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->next = NULL;
	philo->prev = prev;
	philo->id = id;
	philo->dead = 0;
	philo->meals = 0;
	philo->table = table;
	return (philo);
}

int	init(t_table *table)
{
	t_philo			*head;
	unsigned int	i;

	i = 1;
	table->philos = NULL;
	head = NULL;
	while (i <= table->number_of_philosophers)
	{
		table->philos = born(table->philos, i, table);
		if (!table->philos)
			return (free_all(table, 0));
		if (!head)
			head = table->philos;
		else
			table->philos->prev->next = table->philos;
		i++;
	}
	table->philos->next = head;
	head->prev = table->philos;
	table->philos = head;
	return (0);
}
