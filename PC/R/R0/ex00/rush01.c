/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:53 by pbona             #+#    #+#             */
/*   Updated: 2024/08/18 18:38:45 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_top_line(int j, int x)
{
	if (j == 0)
		ft_putchar('/');
	else if (j != x - 1)
		ft_putchar('*');
	else
		ft_putchar('\\');
}
/*1st: left, 2nd: middle, 3rd: right*/

void	ft_middle_lines(int j, int x)
{
	if (j == 0 || j == x - 1)
		ft_putchar('*');
	else
		ft_putchar(' ');
}
/*1st: left and right, 2nd: middle*/

void	ft_bottom_line(int j, int x)
{
	if (j == 0)
		ft_putchar('\\');
	else if (j != x - 1)
		ft_putchar('*');
	else
		ft_putchar('/');
}
/*1st: left, 2nd: middle, 3rd: right*/

void	rush(int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < y && x > 0)
	{
		j = 0;
		while (j < x)
		{
			if (i == 0)
				ft_top_line(j, x);
			else if (i != y -1)
				ft_middle_lines(j, x);
			else
				ft_bottom_line(j, x);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
