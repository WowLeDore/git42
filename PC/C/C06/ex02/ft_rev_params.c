/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 07:59:02 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/21 21:37:43 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	i;

	i = argc;
	while (i > 1)
	{
		i--;
		while (*argv[i])
			write(1, argv[i]++, 1);
		write(1, "\n", 1);
	}
	return (0);
}
