/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:22:27 by mguillot          #+#    #+#             */
/*   Updated: 2025/03/07 16:29:16 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_maillon_icq
{
	int						num;
	struct s_maillon_icq	*next;
}	t_maillon;

typedef struct s_int_circ_queue
{
	int			size;
	t_maillon	*last;
}	t_icq;

void	init_icq(t_icq *q);
int		icq_vide(t_icq *q);
int		icq_enfile(t_icq *q, int valeur);
int		icq_dequeue(t_icq *q);
int		icq_tete(t_icq *q);

char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

#endif
