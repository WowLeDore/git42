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
		return ((int)(t * 255) << 16 | (int)(p * 255) << 8 | (int)(v * 255));
	return ((int)(v * 255) << 16 | (int)(p * 255) << 8 | (int)(q * 255));
}

int	mousepress(int button, int x, int y, t_fract *fo)
{
	if (button == LEFT_CLICK)
		fo->dx += (1.0 / fo->zoom) * (x - fo->width / 2);
	if (button == LEFT_CLICK)
		fo->dy -= (1.0 / fo->zoom) * (y - fo->height / 2);
	if (button == RIGHT_CLICK)
		fo->color_mode = 1 - fo->color_mode;
	if (button == SCROLL_UP)
	{
		if (fo->shift == 1)
			fo->dx += (1.0 / fo->zoom) * (x - fo->width / 2) / 1.25;
		if (fo->shift == 1)
			fo->dy -= (1.0 / fo->zoom) * (y - fo->height / 2) / 1.25;
		fo->zoom *= 1.5;
	}
	if (button == SCROLL_DOWN)
	{
		if (fo->shift == 1)
			fo->dx += (1.0 / fo->zoom) * (x - fo->width / 2) / 1.25;
		if (fo->shift == 1)
			fo->dy -= (1.0 / fo->zoom) * (x - fo->height / 2) / 1.25;
		fo->zoom = fo->zoom / 1.5;
	}
	mlx_clear_window(fo->mlx_ptr, fo->win_ptr);
	plot(fo);
	return (0);
}

int	keypress(int button, t_fract *fo)
{
	fo->ite = 10 * (fo->ite < 10) + fo->ite * (fo->ite >= 10);
	fo->shift *= -(button == LEFT_SHIFT) + (button != LEFT_SHIFT);
	if (button == SPACE)
	{
		fo->dx = 0.0;
		fo->dy = 0.0;
		fo->zoom = 150.0;
	}
	if (button == UP_ARROW)
		fo->dy += 30 / fo->zoom;
	if (button == DOWN_ARROW)
		fo->dy -= 30 / fo->zoom;
	if (button == LEFT_ARROW)
		fo->dx -= 30 / fo->zoom;
	if (button == RIGHT_ARROW)
		fo->dx += 30 / fo->zoom;
	if (button == PLUS)
		fo->ite *= 1.1;
	if (button == MINUS)
		fo->ite *= 0.9;
	if (button == ESC)
		close_win(fo);
	mlx_clear_window(fo->mlx_ptr, fo->win_ptr);
	plot(fo);
	return (0);
}

int	close_win(t_fract *fo)
{
	if (fo->mlx_ptr && fo->img_ptr)
		mlx_destroy_image(fo->mlx_ptr, fo->img_ptr);
	if (fo->mlx_ptr && fo->win_ptr)
		mlx_destroy_window(fo->mlx_ptr, fo->win_ptr);
	if (fo->mlx_ptr)
		mlx_loop_end(fo->mlx_ptr);
	if (fo->mlx_ptr)
		mlx_destroy_display(fo->mlx_ptr);
	if (fo->mlx_ptr)
		free(fo->mlx_ptr);
	exit(0);
	return (0);
}

void	put_pixel(t_fract *fo, int x, int y, int color)
{
	char	*dst;
	int		dx;
	int		dy;

	dx = 0;
	while (dx < fo->scale && x + dx < fo->width)
	{
		dy = 0;
		while (dy < fo->scale && y + dy < fo->height)
		{
			dst = fo->img_adr
				+ ((y + dy) * fo->llen + (x + dx) * (fo->bpp / 8));
			*(unsigned int *)dst = color;
			dy++;
		}
		dx++;
	}
}
