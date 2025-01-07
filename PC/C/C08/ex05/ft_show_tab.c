/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:27:53 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/29 02:38:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stock_str.h"

void	put_str(char *str)
{
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

void	put_nbr(int nb)
{
	int		len;
	int		nb_copy;
	char	digit;

	len = 1;
	nb_copy = nb;
	while (nb_copy > 9)
	{
		nb_copy /= 10;
		len *= 10;
	}
	while (len > 0)
	{
		digit = (nb / len) % 10 + 48;
		len /= 10;
		write(1, &digit, 1);
	}
	write(1, "\n", 1);
}

void	ft_show_tab(struct s_stock_str *par)
{
	int	i;

	i = -1;
	while (par[++i].str)
	{
		put_str(par[i].str);
		put_nbr(par[i].size);
		put_str(par[i].copy);
	}
}
