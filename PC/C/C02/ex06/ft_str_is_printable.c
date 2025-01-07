/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:53:26 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/18 13:49:01 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	int	ascii_value;

	while (*str != '\0')
	{
		ascii_value = *str++;
		if (ascii_value < 32 || ascii_value > 126)
			return (0);
	}
	return (1);
}

//#include <stdio.h>
//int main(){printf("%s","HELLo ! 123");printf("%s"," : ");
//printf("%d",ft_str_is_uppercase("HELLo ! 123"));printf("%s",", Bye !\\n");
//printf("%s"," : ");printf("%d",ft_str_is_uppercase("Bye !\n"));};
