/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:02:25 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/27 13:02:27 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

bool	digit_in_base(char digit, char *base);
int		str_len_base(char *str, char *base);
int		power(int a, int n);

bool	verif_base(char *b_f, char *b_t)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (b_f[++i])
	{
		k = -1;
		while (b_f[++k])
		{
			if ((b_f[i] == b_f[k] && i != k) || b_f[k] == '+' || b_f[k] == '-')
				return (false);
		}
	}
	j = -1;
	while (b_t[++j])
	{
		k = -1;
		while (b_t[++k])
		{
			if ((b_t[j] == b_t[k] && j != k) || b_t[k] == '+' || b_t[k] == '-')
				return (false);
		}
	}
	return (i > 1 && j > 1);
}

int	base_to_dec(char *nbr, char *base)
{
	int	i;
	int	dec;
	int	len;
	int	sign;

	while ((*nbr >= '\t' && *nbr <= '\r') || *nbr == ' ')
		nbr++;
	sign = 1;
	while (*nbr == '+' || *nbr == '-')
		sign *= 2 * (*nbr++ == '+') - 1;
	dec = 0;
	len = str_len_base(nbr, base);
	while (digit_in_base(*nbr, base))
	{
		i = 0;
		while (base[i] != *nbr)
			i++;
		dec += i * power(str_len_base(base, base), --len);
		nbr++;
	}
	return (dec * sign);
}

void	dec_to_base(int nbr, char *base, char *res, int *i)
{
	long	long_nbr;

	long_nbr = nbr;
	if (long_nbr < 0)
		long_nbr = -long_nbr;
	if (nbr < 0)
		res[*i] = '-';
	if (nbr < 0)
		*i = *i + 1;
	if (long_nbr < str_len_base(base, base))
		res[*i] = base[long_nbr];
	else
	{
		dec_to_base(long_nbr / str_len_base(base, base), base, res, i);
		*i = *i + 1;
		dec_to_base(long_nbr % str_len_base(base, base), base, res, i);
	}
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		i;
	int		nbr_dec;
	int		*ptr_to_i;
	char	*result;

	if (!verif_base(base_from, base_to))
		return (0);
	i = 0;
	ptr_to_i = &i;
	result = malloc(34);
	nbr_dec = base_to_dec(nbr, base_from);
	dec_to_base(nbr_dec, base_to, result, ptr_to_i);
	return (result);
}
/*
#include <stdio.h>
int	main(int argc, char *argv[])
{
	if (argc != 4)
		return (0);
	printf("%s",ft_convert_base(argv[1], argv[2], argv[3]));
}
*/