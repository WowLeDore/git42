/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:35:41 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/01 23:35:44 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main.h"

bool	ft_isprintable(char c)
{
	if (c >= 32 && c <= 126)
		return (true);
	return (false);
}

bool	ft_iscolon(char c)
{
	if (c == 58)
		return (true);
	return (0);
}

bool	ft_isnum(char c)
{
	if (c >= 48 && c <= 57)
		return (true);
	return (false);
}

void	ft_init_tab(int tab[4])
{
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
}
