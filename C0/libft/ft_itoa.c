/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:00:35 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:23:41 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(int n)
{
	size_t	len;

	len = (n <= 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*a_num;

	i = ft_numlen(n);
	a_num = malloc(sizeof(char) * (i + 1));
	if (!a_num)
		return (NULL);
	if (n == -2147483648)
		a_num[1] = '2';
	if (n == -2147483648)
		n = -147483648;
	if (n < 0)
		a_num[0] = '-';
	if (n < 0)
		n = -n;
	a_num[i--] = '\0';
	while (n > 9)
	{
		a_num[i--] = (n % 10) + '0';
		n /= 10;
	}
	a_num[i--] = n + '0';
	return (a_num);
}
