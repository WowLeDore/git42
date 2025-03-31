/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:21:24 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/31 13:34:06 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "keys.h"

typedef struct s_fract
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			bpp;
	int			llen;
	int			end;
	char		*img_adr;
	long double	dx;
	long double	dy;
	long double	zoom;
	int			ite;
	int			shift;
	int			color_mode;
	int			type;
	long double	z0_re;
	long double	z0_im;
	long double	cz_re;
	long double	cz_im;
	int			scale;
}	t_fract;

int			eq(char *s1, char *s2);
long double	ft_atolf(char *nptr);
int			ft_printfd(int fd, const char *format, ...);

int			hsv_rgb(long double h, long double s, long double v);
int			mousepress(int button, int x, int y, t_fract *fo);
int			keypress(int button, t_fract *fo);
int			close_win(t_fract *fo);
void		put_pixel(t_fract *fo, int x, int y, int color);

int			verif_args(int argc, char **argv);
void		args(int argc, char **argv, t_fract *fo);

void		plot(t_fract *fo);

#endif
