/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mguillot <mguillot@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/03 17:38:49 by mguillot		  #+#	#+#			 */
/*   Updated: 2025/03/07 18:12:35 by mguillot         ###   ########.fr       */
/*																			*/
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n && *s1 != '\0' && *s1 == *s2)
		n -= 1 + 0 * (*(s1++) * *(s2++));
	return ((n != 0) * ((unsigned char)*s1 - (unsigned char)*s2));
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
