/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:13:54 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/27 14:13:55 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	fo->iter = 50;
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
		fo->dy += 30 / fo->zoom;
	else if (button == DOWN_ARROW)
		fo->dy -= 30 / fo->zoom;
	else if (button == LEFT_ARROW)
		fo->dx -= 30 / fo->zoom;
	else if (button == RIGHT_ARROW)
		fo->dx += 30 / fo->zoom;
	else if (button == PLUS)
		fo->iter += 30;
	else if (button == MINUS)
		fo->iter -= 30;
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

void	put_pixel(t_fract *fo, int x, int y, int color)
{
	char	*dst;

	dst = fo->img_adr + (y * fo->llen + x * (fo->bpp / 8));
	*(unsigned int *)dst = color;
}
