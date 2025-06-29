/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:59:51 by pbona             #+#    #+#             */
/*   Updated: 2024/11/30 21:58:01 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_itoa(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nbr;
	char	*str;

	nbr = n;
	i = ft_len_itoa(nbr);
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	i--;
	if (nbr == 0)
		str [0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		str[i] = '0' + nbr % 10;
		nbr /= 10;
		i--;
	}
	return (str);
}
