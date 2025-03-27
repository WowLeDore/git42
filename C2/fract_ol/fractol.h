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

# define MAX_ITER 50

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "keys.h"
# include "minilibx-linux/mlx.h"

typedef struct s_fract
{
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_adr;
	int		bpp;
	int		llen;
	int		end;
	double	dx;
	double	dy;
	double	zoom;
}	t_fract;

int	ft_printfd(int fd, const char *format, ...);

#endif
