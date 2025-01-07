/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:51:00 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/18 13:52:52 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	capitalized;

	i = 0;
	capitalized = 0;
	while (str[i] != '\0')
	{
		if ('a' <= str[i] && str[i] <= 'z' && capitalized == 0)
		{
			str[i] -= 32;
			capitalized = 1;
		}
		else if (str[i] >= '0' && str[i] <= '9')
			capitalized = 1;
		else if ('A' <= str[i] && str[i] <= 'Z' && capitalized == 1)
			str[i] += 32;
		else if ('A' <= str[i] && str[i] <= 'Z' && capitalized == 0)
			capitalized = 1;
		else if (str[i] < '0' || (str[i] > '9' && str[i] < 'A')
			|| (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
			capitalized = 0;
		i++;
	}
	return (str);
}

//#include <stdio.h>
//int main(){
//char str[]="salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un";
//printf("%s\n",str);ft_strcapitalize(str);printf("%s\n",str);}
