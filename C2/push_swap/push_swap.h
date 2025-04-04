/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:22:27 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/03 16:29:00 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define MAX "2147483648"
# define MIN "-2147483649"

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

void	icq_init(t_icq *q);
int		icq_vide(t_icq *q);
int		icq_enfile(t_icq *q, int valeur, int reverse);
int		icq_defile(t_icq *q);
int		icq_tete(t_icq *q);

char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);

int		verif_all_nbr(char *str);
int		verif_format(char *str);
int		verif_list(int i, char **str);
int		verif_duplicates(t_icq *q);

void	sa(t_icq *a, t_icq *b, t_icq *q);
void	sb(t_icq *a, t_icq *b, t_icq *q);
void	ss(t_icq *a, t_icq *b, t_icq *q);
void	pa(t_icq *a, t_icq *b, t_icq *q);
void	pb(t_icq *a, t_icq *b, t_icq *q);
void	ra(t_icq *a, t_icq *b, t_icq *q);
void	rb(t_icq *a, t_icq *b, t_icq *q);
void	rr(t_icq *a, t_icq *b, t_icq *q);
void	rra(t_icq *a, t_icq *b, t_icq *q);
void	rrb(t_icq *a, t_icq *b, t_icq *q);
void	rrr(t_icq *a, t_icq *b, t_icq *q);

void	bubble(t_icq *a, t_icq *b, t_icq *ope);
void	sort(t_icq *q);

#endif
