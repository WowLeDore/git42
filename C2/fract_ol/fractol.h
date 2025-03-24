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

# define WIDTH 900
# define HEIGHT 900

# include <stdarg.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_adr;
}	t_img;

int	ft_printfd(int fd, const char *format, ...);

#endif
