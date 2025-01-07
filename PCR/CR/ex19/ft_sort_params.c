/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:15:07 by mguillot          #+#    #+#             */
/*   Updated: 2024/11/04 18:23:30 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_str_tab(char **tab, int size)
{
	int		small;
	int		big;

	small = 0;
	while (small < size - 1)
	{
		big = small + 1;
		while (big < size)
		{
			if (ft_strcmp(tab[small], tab[big]) > 0)
				ft_swap(&tab[small], &tab[big]);
			big++;
		}
		small++;
	}
}

int	main(int argc, char *argv[])
{
	int	i;

	ft_sort_str_tab(argv + 1, argc - 1);
	i = 0;
	while (++i < argc)
	{
		while (*argv[i])
			ft_putchar(*(argv[i]++));
		ft_putchar('\n');
	}
	return (0);
}
