/* ************************************************************************** */
/*																		    */
/*														:::      ::::::::   */
/*   libft.c										    :+:      :+:    :+:   */
/*												    +:+ +:+		 +:+     */
/*   By: mguillot <mguillot@student.42.fr>		  +#+  +:+       +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/03 17:38:49 by mguillot		  #+#    #+#		     */
/*   Updated: 2025/03/03 17:40:13 by mguillot		 ###   ########.fr       */
/*																		    */
/* ************************************************************************** */

#include "push_swap.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

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
