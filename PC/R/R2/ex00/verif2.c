/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:36:17 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/01 23:36:19 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main.h"

bool	ft_verif_dict2(char *dict, int *i, int tab[4])
{
	if (dict[*i] == '\n')
	{
		*i += 1;
		return (false);
	}
	ft_init_tab(tab);
	while (ft_isnum(dict[*i]))
	{
		tab[0]++;
		*i += 1;
	}
	while (dict[*i] == ' ')
		*i += 1;
	if (ft_iscolon(dict[*i]))
	{
		tab[1]++;
		*i += 1;
	}
	while (dict[*i] == ' ')
		*i += 1;
	return (true);
}

bool	ft_verif_dict(char *dict)
{
	int	i;
	int	tab[4];

	i = 0;
	while (dict[i])
	{
		if (!ft_verif_dict2(dict, &i, tab))
			continue ;
		while (ft_isprintable(dict[i++]))
			tab[2]++;
		i--;
		while (dict[i++] == '\n')
			tab[3]++;
		i--;
		if (tab[0] == 0 || tab[1] == 0 || tab[2] == 0 || tab[3] == 0)
		{
			ft_putstr("Dict Error\n");
			return (false);
		}
	}
	return (true);
}
