/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:54:51 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/17 18:54:53 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_numeric(char *str)
{
	int	ascii_value;

	while (*str != '\0')
	{
		ascii_value = *str++;
		if (ascii_value < 48 || ascii_value > 57)
			return (0);
	}
	return (1);
}

//#include <stdio.h>
//int main(){printf("%s","420123456789");printf("%s"," : ");
//printf("%d",ft_str_is_numeric("420123456879"));printf("%s",", ");
//printf("%s","O10");printf("%s"," : ");printf("%d",ft_str_is_numeric("O10"));};
