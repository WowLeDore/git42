/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greandre <greandre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:41:43 by greandre          #+#    #+#             */
/*   Updated: 2024/08/25 17:41:47 by greandre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_01.h"

bool	col_up(int grid[N][N], int x, int max_box)
{
	int	y;
	int	box_count;
	int	line[N];

	y = 0;
	box_count = 0;
	while (y < N)
	{
		line[y] = grid[y][x];
		if (grid[y][x] != 0)
			box_count++;
		y++;
	}
	if (box_count == N)
		return (count_boxes(line, 0, N) == max_box);
	return (true);
}

bool	col_down(int grid[N][N], int x, int max_box)
{
	int	y;
	int	box_count;
	int	line[N];

	y = N - 1;
	box_count = 0;
	while (y >= 0)
	{
		line[y] = grid[y][x];
		if (grid[y--][x] != 0)
			box_count++;
	}
	if (box_count == N)
		return (count_boxes(line, N - 1, 0) == max_box);
	return (true);
}

bool	row_left(int grid[N][N], int y, int max_box)
{
	int	x;
	int	box_count;
	int	line[N];

	x = 0;
	box_count = 0;
	while (x < N)
	{
		line[x] = grid[y][x];
		if (grid[y][x] != 0)
			box_count++;
		x++;
	}
	if (box_count == N)
		return (count_boxes(line, 0, N) == max_box);
	return (true);
}

bool	row_right(int grid[N][N], int y, int max_box)
{
	int	x;
	int	box_count;
	int	line[N];

	x = N - 1;
	box_count = 0;
	while (x >= 0)
	{
		line[x] = grid[y][x];
		if (grid[y][x--] != 0)
			box_count++;
	}
	if (box_count == N)
		return (count_boxes(line, N - 1, 0) == max_box);
	return (true);
}

bool	verif_grid(int grid[N][N], int x, int y, int conditions[4*N])
{
	int	i;

	i = 0;
	while (i < N)
	{
		if (grid[y][i] == grid[y][x] && i != x)
			return (false);
		i++;
	}
	i = 0;
	while (i < N)
	{
		if (grid[i][x] == grid[y][x] && i != y)
			return (false);
		i++;
	}
	if (!col_up(grid, x, conditions[x + 0 * N])
		|| !col_down(grid, x, conditions[x + 1 * N])
		|| !row_left(grid, y, conditions[y + 2 * N])
		|| !row_right(grid, y, conditions[y + 3 * N]))
		return (false);
	return (true);
}
