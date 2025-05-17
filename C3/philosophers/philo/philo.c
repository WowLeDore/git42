/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:21:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/17 12:19:52 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*live(void *p)
{
	printf("I am live.");
	return (p);
}

t_fork	*craft(unsigned int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(fork));
	if (!fork)
		return (NULL);
	fork->id = id;
	return (fork);
}

t_philo	*born(t_philo *prev, t_fork *left, unsigned int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(philo));
	if (!philo)
		return (NULL);
	philo->prev = prev;
	philo->left = left;
	philo->id = id;
	pthread_create(&philo->thread, NULL, live, NULL);
	philo->dead = 0;
	philo->right = craft(id);
	philo->next = NULL;
	return (philo);
}

void	think(t_table *table)
{
	unsigned int	i;

	table->philos = born(NULL, NULL, 1);
	i = 2;
	while (i <= table->number_of_philosophers)
	{
		table->philos = born(table->philos, table->philos->right, i);
		table->philos->prev->next = table->philos;
	}
}

int	error(t_errors error)
{
	if (error == OK)
		return (0);
	if (error == ARGC)
		printf("%s\n%s%s%s\n", MSG_ARGC, MSG_USAGE1, MSG_USAGE2, MSG_USAGE3);
	if (error == FORMAT)
		printf("%s\n%s%s%s\n", MSG_FORMAT, MSG_USAGE1, MSG_USAGE2, MSG_USAGE3);
	if (error == PHILO)
		printf("%s\n%s%s%s\n", MSG_PHILO, MSG_USAGE1, MSG_USAGE2, MSG_USAGE3);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (error(parse(argc, argv, &table)))
		return (1);
	think(&table);
	return (0);
}
