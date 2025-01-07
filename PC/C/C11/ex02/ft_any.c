/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:52:02 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/03 16:10:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_any(char **tab, int (*f)(char*))
{
	while (*tab)
	{
		if ((*f)(*(tab++)))
			return (1);
	}
	return (0);
}
/*
#include <stdio.h>

int	a_first_letter(char *str)
{
    return (*str == 'a');
}

int	main()
{
	char *strs1[] = {"hello", "world", "abc", "def", "this is a string", NULL};
	char *strs2[] = {"hello", "world", "bca", "def", "this is a string", NULL};
	printf("%d\n", ft_any(strs1, &a_first_letter));
	printf("%d\n", ft_any(strs2, &a_first_letter));
}
*/
