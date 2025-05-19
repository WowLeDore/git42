/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:40:43 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/19 13:31:31 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

//messages d'erreurs, d'usage
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
	unsigned int	id;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_philo
{
	struct s_philo	*prev;
	t_fork			*left;
	unsigned int	id;
	pthread_t		thread;
	int				dead;
	t_fork			*right;
	struct s_philo	*next;
}	t_philo;

typedef struct s_table
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				philosophers_must_eat;
	unsigned int	number_of_times_each_philosopher_must_eat;
	t_philo			*philos;
}	t_table;

t_errors	parse(int argc, char **argv, t_table *table);

#endif
