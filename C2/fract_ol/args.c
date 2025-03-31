/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:08:55 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/31 16:09:40 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	nbr(char *av)
{
	if (!av || !*av || *av < '0' || *av > '9')
		return (0);
	while (*av >= '0' && *av <= '9')
		av++;
	if (*av && *av != '.')
		return (0);
	if (!*av)
		return (1);
	av++;
	while (*av >= '0' && *av <= '9')
		av++;
	return (!*av);
}

int	verif(int ac, char **av, int fo)
{
	if (fo == 0)
		return (ac == 1 && (eq(av[0], "Mandelbrot") || eq(av[0], "m")));
	else if (fo == 1)
		return (ac == 3 && (eq(av[0], "Julia") || eq(av[0], "j"))
			&& nbr(*(++av)) && nbr(*(++av)));
	else if (fo == 2)
		return (ac == 1 && (eq(av[0], "Burning-Ship") || eq(av[0], "b")));
	return (0);
}

int	verif_args(int ac, char **av)
{
	if (ac == 0 || !av)
		return (ft_printfd(2, "Error: Insufficient arguments.\nUsage: ./fractol"
				" <fractal_type> [x (Julia)] [y (Julia)]\nFractals are Mandelbr"
				"ot (m), Julia (j), Burning-Ship (b).\n") * 0);
	else if (ac > 3)
		return (ft_printfd(2, "Error: Too many arguments.\nUsage: ./fractol"
				" <fractal_type> [x (Julia)] [y (Julia)]\nFractals are Mandelbr"
				"ot (m), Julia (j), Burning-Ship (b).\n") * 0);
	else if (verif(ac, av, 0) || verif(ac, av, 1) || verif(ac, av, 2))
		return (ft_printfd(1, "Help:\n	Left Click to go to point\n	Right Click"
				" to change color mode\n	Scroll Up/Down to zoom/dezoom\n	Lef"
				"t Shift to zoom towards mouse\n	Space to reset zoom and coo"
				"rdinates\n	Arrows for deplacement\n	Plus/Minus to increase/"
				"decrease iterations\n	Echap to quit\n") * 0 + 1);
	else
		return (ft_printfd(2, "Error: Incorrect Usage.\nUsage: ./fractol"
				" <fractal_type> [x (Julia)] [y (Julia)]\nFractals are Mandelbr"
				"ot (m), Julia (j), Burning-Ship (b).\n") * 0);
	return (1);
}

void	args(int ac, char **av, t_fract *fo)
{
	if (verif(ac, av, 0))
		fo->type = 0;
	else if (verif(ac, av, 1))
	{
		fo->type = 1;
		fo->cz_re = ft_atolf(av[1]);
		fo->cz_im = -ft_atolf(av[2]);
	}
	else if (verif(ac, av, 2))
		fo->type = 2;
}
