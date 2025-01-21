/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:12:24 by mguillot          #+#    #+#             */
/*   Updated: 2024/11/25 15:12:38 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int		res;
	char	sign;

	while (('\t' <= *nptr && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	sign = *nptr;
	if (sign == '+' || sign == '-')
		nptr++;
	res = 0;
	while ('0' <= *nptr && *nptr <= '9')
		res = 10 * res + (*(nptr++) - '0');
	return (res * (1 - (sign == '-') * 2));
}
