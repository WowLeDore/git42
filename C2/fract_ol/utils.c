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
	{
		fo->dx += (1.0 / fo->zoom) * (x - fo->width / 2);
		fo->dy += (1.0 / fo->zoom) * (y - fo->height / 2);
	}
	if (button == SCROLL_UP)
	{
		if (fo->shift == 1)
			fo->dx += (1.0 / fo->zoom) * (x - fo->width / 2) / 1.5;
		if (fo->shift == 1)
			fo->dy += (1.0 / fo->zoom) * (y - fo->height / 2) / 1.5;
		fo->zoom *= 1.5;
	}
	if (button == SCROLL_DOWN)
	{
		if (fo->shift == 1)
			fo->dx += (1.0 / fo->zoom) * (x - fo->width / 2) / 1.5;
		if (fo->shift == 1)
			fo->dy += (1.0 / fo->zoom) * (x - fo->height / 2) / 1.5;
		fo->zoom /= 1.5;
	}
	mlx_clear_window(fo->mlx_ptr, fo->win_ptr);
	plot(fo);
	return (0);
}

int	keypress(int button, t_fract *fo)
{
	if (button == LEFT_SHIFT)
		fo->shift *= -1;
	if (button == SPACE)
	{
		fo->dx = 0.0;
		fo->dy = 0.0;
		fo->zoom = 200.0;
	}
	if (button == UP_ARROW)
		fo->dy -= 30 / fo->zoom;
	if (button == DOWN_ARROW)
		fo->dy += 30 / fo->zoom;
	if (button == LEFT_ARROW)
		fo->dx -= 30 / fo->zoom;
	if (button == RIGHT_ARROW)
		fo->dx += 30 / fo->zoom;
	if (button == PLUS)
		fo->ite += 30;
	if (button == MINUS)
		fo->ite -= 30;
	if (button == ESC)
		close_win(fo);
	plot(fo);
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
