/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:06:15 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:28:52 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapi;
	size_t	i;

	if (s && f)
		mapi = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s || !f || !mapi)
		return (NULL);
	i = -1;
	while (s[++i])
		mapi[i] = f(i, s[i]);
	mapi[i] = '\0';
	return (mapi);
}
