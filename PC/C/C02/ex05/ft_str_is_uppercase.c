/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:53:26 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/17 18:59:19 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_uppercase(char *str)
{
	int	ascii_value;

	while (*str != '\0')
	{
		ascii_value = *str++;
		if (ascii_value < 65 || ascii_value > 90)
			return (0);
	}
	return (1);
}

//#include <stdio.h>
//int main(){printf("%s","HELLO");printf("%s"," : ");
//printf("%d",ft_str_is_uppercase("HELLO"));printf("%s",", ");
//printf("%s","hi");printf("%s"," : ");printf("%d",ft_str_is_uppercase("hi"));};
