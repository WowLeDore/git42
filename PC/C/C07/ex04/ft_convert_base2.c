/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:29:21 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/27 19:29:23 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	digit_in_base(char digit, char *base)
{
	while (*base)
	{
		if (digit == *(base++))
			return (true);
	}
	return (false);
}

int	str_len_base(char *str, char *base)
{
	int	len;

	len = 0;
	while (str[len] && digit_in_base(str[len], base))
		len++;
	return (len);
}

int	power(int a, int n)
{
	int	res;

	res = 1;
	while (n > 0)
	{
		res *= a;
		n--;
	}
	return (res);
}
