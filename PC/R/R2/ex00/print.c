/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:35:50 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/01 23:35:52 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main.h"

void	ft_print_nbr_1(char *nbr, struct s_number *dict)
{
	if (nbr == NULL)
		return ;
	while ((*dict).nb_int)
	{
		if (!ft_strcmp((*dict++).nb_int, nbr))
			return (ft_putstr((*(dict - 1)).nb_str));
	}
}

void	ft_print_nbr_2(char *nb, struct s_number *dict)
{
	char	temp[3];
	char	*str;

	if (nb[0] == '1')
		ft_print_nbr_1(nb, dict);
	else
	{
		temp[0] = nb[0];
		temp[1] = '0';
		temp[2] = '\0';
		ft_print_nbr_1(temp, dict);
		if (nb[1] != '0')
		{
			write(1, "-", 1);
			str = ft_strndup(&nb[1], 2);
			ft_print_nbr_1(str, dict);
			free(str);
		}
	}
}

void	ft_print_nbr_3(char *nb, struct s_number *dict)
{
	char	*str;

	if (nb[0] != '0')
	{
		str = ft_strndup(&nb[0], 2);
		ft_print_nbr_1(str, dict);
		free(str);
		write(1, " ", 1);
		ft_print_nbr_1("100", dict);
		if (nb[1] != '0' || nb[2] != '0')
			write(1, " ", 1);
	}
	if (nb[1] == '0' && nb[2] != '0')
	{
		str = ft_strndup(&nb[2], 2);
		ft_print_nbr_1(str, dict);
		free(str);
	}
	else
		ft_print_nbr_2(nb + 1, dict);
}

void	ft_print_nbr(char *nbr, struct s_number *dict)
{
	if (ft_strlen(nbr) == 1)
		ft_print_nbr_1(nbr, dict);
	else if (ft_strlen(nbr) == 2)
		ft_print_nbr_2(nbr, dict);
	else
		ft_print_nbr_3(nbr, dict);
}
