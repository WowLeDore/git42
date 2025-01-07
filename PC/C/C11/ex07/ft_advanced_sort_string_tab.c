/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_string_tab.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:46:34 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/04 17:01:13 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	array_size(char **tab)
{
	int	size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

void	ft_advanced_sort_string_tab(char **tab, int (*cmp)(char *, char *))
{
	int	small;
	int	size;
	int	big;

	size = array_size(tab);
	small = 0;
	while (small < size - 1)
	{
		big = small + 1;
		while (big < size)
		{
			if ((*cmp)(tab[small], tab[big]) > 0)
				swap(&tab[small], &tab[big]);
			big++;
		}
		small++;
	}
}
/*
#include <unistd.h>

int     str_cmp(char *s1, char *s2)
{
        while (*s1 != '\0' && *s2 != '\0')
        {
                if (*s1 != *s2)
                {
                        return (*s1 - *s2);
                }
                s1++;
                s2++;
        }
        return (*s1 - *s2);
}

int	str_len_cmp(char *s1, char *s2)
{
	int	size1;
	int	size2;

	size1 = 0;
	size2 = 0;
	while (s1[size1])
		size1++;
	while (s2[size2])
		size2++;
	return (size1 - size2);
}

int	main(int argc, char *argv[])
{
	int	i;

	ft_advanced_sort_string_tab(argv + 1, &str_cmp);
	i = 1;
	while (i < argc)
	{
		while (*argv[i])
			write(1, argv[i]++, 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
*/
