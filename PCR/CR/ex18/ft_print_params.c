/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 07:59:02 by mguillot          #+#    #+#             */
/*   Updated: 2024/11/04 18:21:39 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int	main(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		while (*argv[i])
			ft_putchar(*(argv[i]++));
		ft_putchar('\n');
	}
	return (0);
}
