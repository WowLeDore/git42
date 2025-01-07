/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:54:21 by mguillot          #+#    #+#             */
/*   Updated: 2024/08/17 19:26:53 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *str)
{
	int	ascii_value;

	while (*str != '\0')
	{
		ascii_value = *str++;
		if (!((ascii_value > 64 && ascii_value < 91)
				|| (ascii_value > 96 && ascii_value < 123)))
			return (0);
	}
	return (1);
}

//#include <stdio.h>
//int main(){printf("%s","Hello");printf("%s"," : ");
//printf("%d",ft_str_is_alpha("Hello"));printf("%s",", ");
//printf("%s","bye!");printf("%s"," : ");printf("%d",ft_str_is_alpha("bye!"));};
