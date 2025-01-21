/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:55:46 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:26:50 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*chr;

	chr = ft_strchr(s, c);
	while (chr && *chr && ft_strchr(chr + 1, c))
		chr = ft_strchr(chr + 1, c);
	return (chr);
}
