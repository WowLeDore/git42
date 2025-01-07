/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greandre <greandre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:49:18 by greandre          #+#    #+#             */
/*   Updated: 2024/08/24 16:41:01 by greandre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_01.h"

void	print_grid(int grid[N][N])
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < N)
	{
		x = 0;
		while (x < N)
		{
			c = grid[y][x] + '0';
			write(1, &c, 1);
			if (x != N - 1)
				write(1, " ", 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}

int	count_boxes(int line[N], int start, int end)
{
	int	i;
	int	prev_box;
	int	box_count;

	i = start;
	box_count = 0;
	prev_box = line[i];
	while ((i < end && end > start) || (i >= end && end < start))
	{
		if (line[i] != 0 && line[i] >= prev_box)
		{
			box_count++;
			prev_box = line[i];
		}
		if (end > start)
			i++;
		else
			i--;
	}
	return (box_count);
}

void	make_grid(int grid[N][N], int conditions[4*N], int i, bool *found)
{
	int	x;
	int	y;
	int	box;

	if (i == N * N)
	{
		if (!*found)
			print_grid(grid);
		*found = true;
		return ;
	}
	if (N < 1)
		return ;
	x = i % N;
	y = i / N;
	box = 1;
	while (box <= N)
	{
		grid[y][x] = box;
		if (verif_grid(grid, x, y, conditions) && !*found)
			make_grid(grid, conditions, i + 1, found);
		grid[y][x] = 0;
		box++;
	}
}

void	make_empty_grid(int grid[N][N])
{
	int	x;
	int	y;

	y = 0;
	while (y < N)
	{
		x = 0;
		while (x < N)
		{
			grid[y][x] = 0;
			x++;
		}
		y++;
	}
}

int	main(int argc, char *argv[])
{
	int		grid[N][N];
	int		conditions[4 * N];
	bool	found;
	bool	*ptr_to_found;

	if (N < 1 || !verif_args(argc, argv))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	found = false;
	ptr_to_found = &found;
	if (N == 1)
	{
		grid[0][0] = 1;
		print_grid(grid);
		found = true;
	}
	make_empty_grid(grid);
	convert_conditions(argv, conditions);
	make_grid(grid, conditions, 0, ptr_to_found);
	if (!found)
		write(1, "Error\n", 6);
	return (0);
}
