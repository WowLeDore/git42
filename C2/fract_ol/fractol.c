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

void	init(t_fract *fo)
{
	fo->width = 600;
	fo->height = 400;
	fo->mlx_ptr = mlx_init();
	fo->win_ptr = mlx_new_window(fo->mlx_ptr, fo->width, fo->height, "fractol");
	fo->img_ptr = mlx_new_image(fo->mlx_ptr, fo->width, fo->height);
	fo->img_adr = mlx_get_data_addr(fo->img_ptr, &fo->bpp, &fo->llen, &fo->end);
	fo->dx = 0.0;
	fo->dy = 0.0;
	fo->zoom = 200.0;
	fo->ite = 50;
	fo->shift = -1;
}

int	comp(t_fract *fo)
{
	int			j;
	long double	tmp;
	long double	re;
	long double	im;

	re = fo->z0_re;
	im = fo->z0_im;
	j = -1;
	while (++j < fo->ite)
	{
		if (re * re + im * im > __DBL_MAX__)
			return (j);
		tmp = re;
		re = re * re - im * im + fo->cz_re;
		im = 2.0 * tmp * im + fo->cz_im;
	}
	return (fo->ite);
}

void	var(t_fract *fo, long double x, long double y)
{
	if (fo->type == 0)
	{
		fo->z0_re = 0;
		fo->z0_im = 0;
		fo->cz_re = (1 / fo->zoom) * (x - fo->width / 2) + fo->dx;
		fo->cz_im = (1 / fo->zoom) * (y - fo->height / 2) - fo->dy;
	}
	else if (fo->type == 1)
	{
		fo->z0_re = (1 / fo->zoom) * (x - fo->width / 2) + fo->dx;
		fo->z0_im = (1 / fo->zoom) * (y - fo->height / 2) - fo->dy;
	}
}

//color = hsv_rgb(ite / (long double)(fo->ite), 1.0, 1.0);
void	plot(t_fract *fo)
{
	long double	x;
	long double	y;
	int			ite;
	int			color;

	mlx_clear_window(fo->mlx_ptr, fo->win_ptr);
	x = -1;
	while (++x < fo->width)
	{
		y = -1;
		while (++y < fo->height)
		{
			var(fo, x, y);
			ite = comp(fo);
			color = 0x631416;
			if (ite < fo->ite)
				color *= ite;
			put_pixel(fo, x, fo->height - y, color);
		}
	}
	put_pixel(fo, fo->width / 2 - 1, fo->height / 2, 0xFFFFFF);
	put_pixel(fo, fo->width / 2 + 1, fo->height / 2, 0xFFFFFF);
	put_pixel(fo, fo->width / 2, fo->height / 2 - 1, 0xFFFFFF);
	put_pixel(fo, fo->width / 2, fo->height / 2 + 1, 0xFFFFFF);
	mlx_put_image_to_window(fo->mlx_ptr, fo->win_ptr, fo->img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_fract	fo;

	init(&fo);
	if (!verif_args(argc - 1, argv + 1))
		exit(1);
	else
		args(argc - 1, argv + 1, &fo);
	plot(&fo);
	mlx_mouse_hook(fo.win_ptr, mousepress, &fo);
	mlx_key_hook(fo.win_ptr, keypress, &fo);
	mlx_hook(fo.win_ptr, 17, 0, close_win, &fo);
	mlx_loop(fo.mlx_ptr);
	return (0);
}
