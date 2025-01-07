/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:02:50 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/03 16:08:41 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int length, int (*f)(char*))
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < length)
	{
		if ((*f)(tab[i++]))
			count++;
	}
	return (count);
}
/*
#include <stdio.h>

int	a_first_letter(char *str)
{
    return (*str == 'a');
}

int	main()
{
	char *strs1[5] = {"ahello", "world", "abc", "def", "athis is a string"};
	char *strs2[5] = {"hello", "world", "bca", "def", "this is a string"};
	printf("%d\n", ft_count_if(strs1, 5, &a_first_letter));
	printf("%d\n", ft_count_if(strs2, 5, &a_first_letter));
}
*/
