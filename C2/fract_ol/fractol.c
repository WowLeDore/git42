/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:01:16 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/24 17:30:31 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_img	img;

	if (argc != 2 || !argv)
		return (1 + 0 * ft_printfd(2, "Error. Usage : ./fractol <fractal>\n"
				"Fractals : mandelbrot (m), julia (j)\n"));
	if (argv[1][0] == 'm')
	{
		mlx.mlx_ptr = mlx_init();
		mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Fract'ol");
		mlx_loop(mlx.mlx_ptr);
	}
	return (0);
}
