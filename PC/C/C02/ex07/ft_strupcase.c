/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:27:12 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/17 19:40:00 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
		i++;
	}
	return (str - i);
}

//#include <stdio.h>
//int main(){char str1[]="hello world";char str2[]="aBcDeF 1 2 !";
//printf("Original: %s\n", str1);ft_strupcase(str1);
//printf("Uppercase: %s\n\n", str1);printf("Original: %s\n", str2);
//ft_strupcase(str2);printf("Uppercase: %s\n", str2);}
