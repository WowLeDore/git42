/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:59:54 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/20 22:11:50 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;
	int	len_str;
	int	len_to_find;

	if (*to_find == '\0')
		return (str);
	len_to_find = 0;
	while (to_find[len_to_find] != '\0')
		len_to_find++;
	len_str = 0;
	while (str[len_str] != '\0')
		len_str++;
	i = 0;
	while (i <= len_str - len_to_find)
	{
		j = 0;
		while (j < len_to_find && str[i + j] == to_find[j])
			j++;
		if (j == len_to_find)
			return (str + i);
		i++;
	}
	return (0);
}
//#include <stdio.h>
//int main(){char str[]="i12";char to_find[]="123";
//char *result=ft_strstr(str,to_find);printf("%s\n",result);}
