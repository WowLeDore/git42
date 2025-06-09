/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:40:43 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/09 11:46:58 by mguillot         ###   ########.fr       */
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
# define MSG_ALLOC "Error: Memory allocation failed.\n"
# define MSG_MUTEX "Error: A mutex was not initialized correctly.\n"
# define MSG_THREAD "Error: A thread was not initialized correctly.\n"
# define MSG_TIME "Error: The gettime has returned an error.\n"

# define MSG_USAGE1 "Usage: ./philo <number_of_philosophers> "
# define MSG_USAGE2 "<time_to_die> <time_to_eat> <time_to_sleep>"
# define MSG_USAGE3 " [number_of_times_each_philosopher_must_eat]"

typedef enum e_errors
{
	OK,
	ARGC,
	FORMAT,
	PHILO,
	ALLOC,
	MUTEX,
	THREAD,
	TIME
}	t_errors;

typedef struct s_philo
{
	unsigned int		id;
	struct s_table		*table;
	int					dead;
	unsigned long long	dead_time;
}	t_philo;

typedef struct s_table
{
	unsigned int		number_of_philosophers;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					philosophers_must_eat;
	unsigned int		number_of_times_each_philosopher_must_eat;
	t_philo				*philos;
	pthread_t			*threads;
	pthread_mutex_t		*mutexes;
	unsigned long long	timer;
	pthread_mutex_t		print;
	int					dead;
}	t_table;

t_errors	parse(int argc, char **argv, t_table *table);
int			error(t_errors error);

#endif
