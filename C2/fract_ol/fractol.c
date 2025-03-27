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

int	comp(long double x, long double y, int max_iter)
{
	int			i;
	long double	re;
	long double	im;
	long double	tmp;

	re = 0.0;
	im = 0.0;
	i = -1;
	while (++i < max_iter)
	{
		if (re * re + im * im > 4)
			return (i);
		tmp = re;
		re = re * re - im * im + x;
		im = 2.0 * tmp * im + y;
	}
	return (max_iter);
}

int	hsv_rgb(long double h, long double s, long double v)
{
	long double	p;
	long double	q;
	long double	t;
	long double	f;
	int			i;

	if (s == 0)
		return ((int)(v * 255) << 16 | (int)(v * 255) << 8 | (int)(v * 255));
	h *= 6.0;
	i = (int)h;
	f = h - i;
	p = v * (1.0 - s);
	q = v * (1.0 - s * f);
	t = v * (1.0 - s * (1.0 - f));
	if (i == 0)
		return ((int)(v * 255) << 16 | (int)(t * 255) << 8 | (int)(p * 255));
	else if (i == 1)
		return ((int)(q * 255) << 16 | (int)(v * 255) << 8 | (int)(p * 255));
	else if (i == 2)
		return ((int)(p * 255) << 16 | (int)(v * 255) << 8 | (int)(t * 255));
	else if (i == 3)
		return ((int)(p * 255) << 16 | (int)(q * 255) << 8 | (int)(v * 255));
	else if (i == 4)
		return ((int)(v * 255) << 16 | (int)(p * 255) << 8 | (int)(t * 255));
	return ((int)(v * 255) << 16 | (int)(p * 255) << 8 | (int)(q * 255));
}


void	mandelbrot(t_fract *fo)
{
	long double	x;
	long double	y;
	int			iter;
	int			color;

	x = -1;
	while (++x < fo->width)
	{
		y = -1;
		while (++y < fo->height)
		{
			iter = comp((1 / fo->zoom) * (x - fo->width / 2) + fo->dx,
					(1 / fo->zoom) * (y - fo->height / 2) - fo->dy, fo->ite);
			color = hsv_rgb(0, 0, 0);
			if (iter < fo->ite)
				color = hsv_rgb(iter / (long double)(fo->ite), 1.0, 1.0);
			put_pixel(fo, x, y, color);
		}
	}
	put_pixel(fo, fo->width / 2, fo->height / 2, 0x00FFFFFF);
	mlx_put_image_to_window(fo->mlx_ptr, fo->win_ptr, fo->img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_fract	fo;

	if (argc != 2)
	{
		return (1 + 0 * ft_printfd(2, "Error. Usage : ./fool <foal>\n"
				"foals : mandelbrot (m), julia (j)\n"));
		exit(1);
	}
	init(&fo);
	if (argv[1][0] == 'm')
		mandelbrot(&fo);
	else
		ft_printfd(2, "Error. Usage : ./fractol <fractal>\n"
			"fractals : mandelbrot (m), julia (j)\n");
	mlx_mouse_hook(fo.win_ptr, mousepress, &fo);
	mlx_key_hook(fo.win_ptr, keypress, &fo);
	mlx_hook(fo.win_ptr, 17, 0, close_win, &fo);
	mlx_loop(fo.mlx_ptr);
	return (0);
}
