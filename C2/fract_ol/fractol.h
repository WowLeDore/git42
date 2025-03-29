/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:21:24 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/24 17:30:45 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "keys.h"
# include "minilibx-linux/mlx.h"

typedef struct s_fract
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_adr;
	int			bpp;
	int			llen;
	int			end;
	int			type;
	long double	dx;
	long double	dy;
	long double	zoom;
	int			ite;
	long double	z0_re;
	long double	z0_im;
	long double	cz_re;
	long double	cz_im;
}	t_fract;

int		ft_printfd(int fd, const char *format, ...);
int		mousepress(int button, int x, int y, t_fract *fo);
int		keypress(int button, t_fract *fo);
int		close_win(t_fract *fo);
void	plot(t_fract *fo);
void	put_pixel(t_fract *fo, int x, int y, int color);
int		hsv_rgb(long double h, long double s, long double v);

#endif
