/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:13:39 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:16:38 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*call;

	if (nmemb * size == 0)
		call = malloc(1);
	else
		call = malloc(nmemb * size);
	if (!call)
		return (NULL);
	ft_bzero(call, size * nmemb);
	return (call);
}
