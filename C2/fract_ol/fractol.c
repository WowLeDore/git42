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

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->img_adr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	comp(double x, double y)
{
	int		i;
	double	re;
	double	im;
	double	tmp;

	re = 0.0;
	im = 0.0;
	i = -1;
	while (++i < MAX_ITER)
	{
		if (re * re + im * im > 4)
			return (i);
		if (re < 0)
			re *= -1;
		if (im < 0)
			im *= -1;
		tmp = re;
		re = re * re - im * im + x;
		im = 2.0 * tmp * im + y;
	}
	return (MAX_ITER);
}

void	mandelbrot(t_mlx *mlx)
{
	double	x;
	double	y;
	int		iter;
	int		color;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			iter = comp((1 / ZOOM) * (x - WIDTH / 2) + DX,
					(1 / ZOOM) * (y - HEIGHT / 2) - DY);
			color = 0x000000FF;
			if (iter < MAX_ITER)
				color = 0xFF * (iter / MAX_ITER);
			put_pixel(mlx->img, x, y, color);
		}
	}
	put_pixel(mlx->img, WIDTH / 2, HEIGHT / 2, 0x00FFFFFF);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img->img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2 || !argv)
		return (1 + 0 * ft_printfd(2, "Error. Usage : ./fractol <fractal>\n"
				"Fractals : mandelbrot (m), julia (j)\n"));
	if (argv[1][0] == 'm')
	{
		mlx.mlx_ptr = mlx_init();
		mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Fract'ol");
		mlx.img->img_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
		mlx.img->img_adr = mlx_get_data_addr(mlx.img->img_ptr, &mlx.img->bpp,
				&mlx.img->llen, &mlx.img->endi);
		mandelbrot(&mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	return (0);
}
