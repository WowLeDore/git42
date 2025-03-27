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

void	put_pixel(t_fract *fo, int x, int y, int color)
{
	char	*dst;

	dst = fo->img_adr + (y * fo->llen + x * (fo->bpp / 8));
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
		tmp = re;
		re = re * re - im * im + x;
		im = 2.0 * tmp * im + y;
	}
	return (MAX_ITER);
}

void	mandelbrot(t_fract *fo)
{
	double	x;
	double	y;
	int		iter;
	int		color;

	x = -1;
	while (++x < fo->width)
	{
		y = -1;
		while (++y < fo->height)
		{
			iter = comp((1 / fo->zoom) * (x - fo->width / 2) + fo->dx,
					(1 / fo->zoom) * (y - fo->height / 2) - fo->dy);
			color = 0x000000FF;
			if (iter < MAX_ITER)
				color = 0xFF * (iter / MAX_ITER);
			put_pixel(fo, x, y, color);
		}
	}
	put_pixel(fo, fo->width / 2, fo->height / 2, 0x00FFFFFF);
	mlx_put_image_to_window(fo->mlx_ptr, fo->win_ptr, fo->img_ptr, 0, 0);
}

void	init(t_fract *fo)
{
	fo->width = 900;
	fo->height = 900;
	fo->mlx_ptr = mlx_init();
	fo->win_ptr = mlx_new_window(fo->mlx_ptr, fo->width, fo->height, "fo'ol");
	fo->img_ptr = mlx_new_image(fo->mlx_ptr, fo->width, fo->height);
	fo->img_adr = mlx_get_data_addr(fo->img_ptr, &fo->bpp, &fo->llen, &fo->end);
	fo->dx = 0.0;
	fo->dy = 0.0;
	fo->zoom = 200.0;
}

int	mousepress(int button, int x, int y, t_fract *fo)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
		fo->zoom *= 1.2;
	else if (button == SCROLL_DOWN)
		fo->zoom /= 1.2;
	mlx_clear_window(fo->mlx_ptr, fo->win_ptr);
	mandelbrot(fo);
	return (0);
}

int	keypress(int button, t_fract *fo)
{
	if (button == UP_ARROW)
		fo->dy += 10 / fo->zoom;
	else if (button == DOWN_ARROW)
		fo->dy -= 10 / fo->zoom;
	else if (button == LEFT_ARROW)
		fo->dx -= 10 / fo->zoom;
	else if (button == RIGHT_ARROW)
		fo->dx += 10 / fo->zoom;
	else if (button == ESC)
	{
		mlx_destroy_window(fo->mlx_ptr, fo->win_ptr);
		exit(0);
	}
	mlx_clear_window(fo->mlx_ptr, fo->win_ptr);
	mandelbrot(fo);
	return (0);
}

int	close_win(t_fract *fo)
{
	mlx_destroy_window(fo->mlx_ptr, fo->win_ptr);
	exit(0);
	return (0);
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
