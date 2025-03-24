/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:01:16 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/24 17:26:35 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv)
	{
		ft_printfd(2, "Error. Usage : ./fractol <fractal>\n"
				"Fractals : mandelbrot (m), julia (j)\n");
		return (1);
	}
	if (argv[1][0] == 'm')
		ft_printfd(1, "Mandel\n");
	ft_printfd(1, 0);
	return (0);
}
