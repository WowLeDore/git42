/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:40:43 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/22 15:13:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define MSG_ARGC "Error: Incorrect number of arguments."
# define MSG_FORMAT "Error: All arguments must be unsigned integers."
# define MSG_PHILO "Error: There should be at least one philosopher."
# define MSG_USAGE1 "Usage: ./philo <number_of_philosophers> "
# define MSG_USAGE2 "<time_to_die> <time_to_eat> <time_to_sleep>"
# define MSG_USAGE3 " [number_of_times_each_philosopher_must_eat]"

typedef enum e_errors
{
	OK,
	ARGC,
	FORMAT,
	PHILO
}	t_errors;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	unsigned int	id;
}	t_fork;

typedef struct s_philo
{
	t_fork			*right;
	t_fork			*left;
	struct s_philo	*next;
	struct s_philo	*prev;
	unsigned int	id;
	int				dead;
	unsigned int	meals;
	struct s_table	*table;
	pthread_t		thread;
}	t_philo;

typedef struct s_table
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				philosophers_must_eat;
	unsigned int	number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	lock;
	int				start;
	unsigned long	timer;
	t_philo			*philos;
}	t_table;

t_errors	parse(int argc, char **argv, t_table *table);
int			error(t_errors error);

#endif
