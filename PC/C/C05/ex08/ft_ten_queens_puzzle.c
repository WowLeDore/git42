/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 00:43:12 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/23 00:43:20 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>

void	ft_print_grid(int grid[10])
{
	int		x;
	char	c;

	x = 0;
	while (x < 10)
	{
		c = grid[x++] + '0';
		write(1, &c, 1);
	}
	write(1, "\n", 1);
}

bool	ft_verif_grid(int grid[10], int x, int y)
{
	int	i;

	i = 0;
	while (i < x)
	{
		if (grid[i] == y || grid[i] - i == y - x || grid[i] + i == y + x)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_make_grid(int grid[10], int x, int *count)
{
	int	y;

	if (x == 10)
	{
		ft_print_grid(grid);
		(*count)++;
		return ;
	}
	y = 0;
	while (y < 10)
	{
		if (ft_verif_grid(grid, x, y))
		{
			grid[x] = y;
			ft_make_grid(grid, x + 1, count);
		}
		y++;
	}
}

int	ft_ten_queens_puzzle(void)
{
	int	count;
	int	grid[10];

	count = 0;
	ft_make_grid(grid, 0, &count);
	return (count);
}
/*
int main()
{
	ft_ten_queens_puzzle();
}*/
