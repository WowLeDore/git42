/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbona <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:44:07 by pbona             #+#    #+#             */
/*   Updated: 2024/12/07 22:57:57 by pbona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_up;

	if (!*lst)
		return ;
	while (*lst != NULL)
	{
		lst_up = (*lst)-> next;
		del ((*lst)-> content);
		free (*lst);
		*lst = lst_up;
	}
}
