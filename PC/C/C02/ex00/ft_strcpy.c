/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:46:49 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/16 14:12:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	int	len;

	len = 0;
	while (*src != '\0')
	{
		*dest = *src;
		len++;
		src++;
		dest++;
	}
	*dest = *src;
	return (dest - len);
}

//#include <stdio.h>
//int main(){char src[]="Hello, World!";char dest[15];
//ft_strcpy(dest,src);printf("%s\n",dest);}
