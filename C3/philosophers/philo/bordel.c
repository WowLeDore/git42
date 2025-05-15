/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bordel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:37:57 by mguillot          #+#    #+#             */
/*   Updated: 2025/05/14 19:13:06 by mguillot         ###   ########.fr       */
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
