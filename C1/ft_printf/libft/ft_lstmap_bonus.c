/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:56:02 by mguillot          #+#    #+#             */
/*   Updated: 2024/12/02 15:31:56 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*map_tmp;
	t_list	*lst_tmp;

	if (!lst || !f || !del)
		return (NULL);
	mapped = ft_lstnew(f((*lst).content));
	map_tmp = mapped;
	lst_tmp = lst;
	while ((*lst_tmp).next && map_tmp)
	{
		lst_tmp = (*lst_tmp).next;
		(*map_tmp).next = ft_lstnew(f((*lst_tmp).content));
		map_tmp = (*map_tmp).next;
	}
	if (map_tmp)
		return (mapped);
	ft_lstclear(&mapped, del);
	return (NULL);
}
