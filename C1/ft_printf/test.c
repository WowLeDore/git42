/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 02:16:01 by mguillot          #+#    #+#             */
/*   Updated: 2025/01/11 03:08:23 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	put_char(void *c)
{
	printf("%c", *(char *)c);
}

void	put_str(void *str)
{
	printf("%s", (char *)str);
}

void	put_ptr(void *ptr)
{
	printf("%p", ptr);
}

void	put_nbr(void *nbr)
{
	printf("%d", *(int *)nbr);
}

void	put_unbr(void *unbr)
{
	printf("%u", *(int *)unbr);
}

void	put_lhex(void *hex)
{
	printf("%x", *(int *)hex);
}

void	put_bhex(void *hex)
{
	printf("%X", *(int *)hex);
}

void	put_flag(char flag, void *arg)
{
	int		i;
	char	*flags;
	void	(*funcs[8])(void *);

	flags = "cspdiuxX";
	funcs[0] = put_char;
	funcs[1] = put_str;
	funcs[2] = put_ptr;
	funcs[3] = put_nbr;
	funcs[4] = put_nbr;
	funcs[5] = put_unbr;
	funcs[6] = put_lhex;
	funcs[7] = put_bhex;
	i = -1;
	while (++i < 9)
	{
		if (flags[i] == flag)
			funcs[i](arg);
	}
}

int	main(void)
{
	put_flag('s', (void *)"Hello !");
}
