/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 04:10:40 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/21 04:12:09 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_char_in_str(char *str, char to_find)
{
	while (*str != to_find && *str != '\0')
		str++;
	if (*str)
		return (1);
	return (0);
}

int	ft_strlen_in_base(char *str, char *base)
{
	int	len;

	len = 0;
	while (ft_char_in_str(base, str[len]))
		len++;
	return (len);
}

int	ft_base_illegale(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		if (base[i] == '-' || base[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	ft_a_to_the_b(int a, int b)
{
	int	res;

	res = 1;
	while (b > 0)
	{
		res *= a;
		b--;
	}
	return (res);
}

int	ft_atoi_base(char *str, char *base)
{
	int	strlen;
	int	sign;
	int	res;
	int	i;
	int	j;

	if (ft_strlen_in_base(base, base) <= 1 || ft_base_illegale(base))
		return (0);
	sign = 1;
	res = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
		sign *= 2 * (*str++ != '-') - 1;
	j = 0;
	strlen = ft_strlen_in_base(str, base);
	while (ft_char_in_str(base, *str))
	{
		i = 0;
		while (base[i] != *str)
			i++;
		res += i * ft_a_to_the_b(ft_strlen_in_base(base, base), strlen - ++j);
		str++;
	}
	return (res * sign);
}
/*
#include <stdio.h>
int	main(int argc,char **argv)
{
	if (argc == 3)
		printf("Number : %s, Base : %s ; Decimal : %d\n", argv[1], argv[2],
			ft_atoi_base(argv[1], argv[2]));
}
*/
