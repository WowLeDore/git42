/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:23:22 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/07 16:28:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	verif(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		while (*str >= '0' && *str <= '9')
			str++;
		if (*str && (*(str++) != ' ' || !*str))
			return (0);
	}
	return (1);
}

int	count(char *str, char c)
{
	int	nb;

	nb = 0;
	while (str && *str)
		nb = nb + (*(str++) == c);
	return (nb);
}

int	*s_to_l(char *str)
{
	int	nb_nb;
	int	*l;

	if (!verif(str))
		return (NULL);
	nb_nb = count(str, ' ');
	while (*str)
	{

	}
}

int	main(int argc, char **argv)
{
	int	*a;

	if (argc < 2)
		return (0);
	if (argc == 2 && ft_strchr(argv[1], ' '))
		a = s_to_l(argv[1]);
	//else
	//	a = sl_to_l(argc - 1, argv + 1);
	if (!a)
		return (1 + 0 * ft_printf_fd(1 ,"Error\n"));
	//sort(a);
}
