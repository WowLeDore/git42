/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:45:43 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/20 18:51:27 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	int	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	while (*src != '\0')
		dest[i++] = *src++;
	dest[i] = '\0';
	return (dest);
}
//#include <stdio.h>
//int main(){char dest[20] = "Hello, ";char src[] = "world!";
//ft_strcat(dest, src);printf("%s\n", dest);}
