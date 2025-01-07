/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:20:10 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/16 14:16:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	len;

	len = 0;
	while (*src != '\0' && len < n)
	{
		*dest = *src;
		len++;
		src++;
		dest++;
	}
	while (len < n)
	{
		*dest = '\0';
		dest++;
		len++;
	}
	return (dest - len);
}

//#include <stdio.h>
//int main(){char src[]="Hello, World!";char dest[15];
//ft_strncpy(dest,src,5);printf("%s\n",dest);}
