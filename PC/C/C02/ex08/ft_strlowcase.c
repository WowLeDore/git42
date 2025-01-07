/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:27:12 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/17 19:42:09 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
		str++;
		i++;
	}
	return (str - i);
}

//#include <stdio.h>
//int main(){char str1[]="HELLO WORLD";char str2[]="aBcDeF 1 2 !";
//printf("Original: %s\n", str1);ft_strlowcase(str1);
//printf("Lowercase: %s\n\n", str1);printf("Original: %s\n", str2);
//ft_strlowcase(str2);printf("Lowercase: %s\n", str2);}
