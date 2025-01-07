/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:36:43 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/01 23:36:45 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main.h"

void	ft_print_whole_nb2(int pow, struct s_number *dict)
{
	char	*str;

	write(1, " ", 1);
	str = ft_ten_pow(pow);
	ft_print_nbr_1(str, dict);
	free(str);
}

void	ft_print_whole_nb(char **nbrs, struct s_number *dict)
{
	int		i;
	int		pow;

	i = ft_arraylen(nbrs) - 1;
	pow = i * 3;
	if (!ft_strcmp(*nbrs, "000") && !*(nbrs + 1))
		ft_print_nbr_1("0", dict);
	if (!ft_strcmp(*nbrs, "000") && !*(nbrs + 1))
		free(*nbrs);
	else
	{
		while (i >= 0)
		{
			ft_print_nbr(nbrs[i], dict);
			if ((nbrs[i][0] != '0' || nbrs[i][1] != '0' || nbrs[i][2] != '0')
				&& i != 0)
				ft_print_whole_nb2(pow, dict);
			free(nbrs[i]);
			pow -= 3;
			i--;
			if (i >= 0 && (nbrs[i][0] != '0'
				|| nbrs[i][1] != '0' || nbrs[i][2] != '0'))
				write(1, " ", 1);
		}
	}
}
