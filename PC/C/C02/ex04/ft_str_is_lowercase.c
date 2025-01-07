/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:53:26 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/17 18:56:35 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	int	ascii_value;

	while (*str != '\0')
	{
		ascii_value = *str++;
		if (ascii_value < 97 || ascii_value > 122)
			return (0);
	}
	return (1);
}

//#include <stdio.h>
//int main(){printf("%s","hello");printf("%s"," : ");
//printf("%d",ft_str_is_lowercase("hello"));printf("%s",", ");
//printf("%s","Hi");printf("%s"," : ");printf("%d",ft_str_is_lowercase("Hi"));};
