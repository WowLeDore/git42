/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:21:10 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/14 19:15:06 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_error(t_errors error)
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
	t_philo	philo;

	if (put_error(parse(argc, argv, &philo)))
		return (1);
	return (0);
}
