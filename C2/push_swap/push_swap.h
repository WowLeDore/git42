/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:04:29 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/10 17:04:30 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define MAX "2147483648"
# define MIN "-2147483649"

# define DIVS 9

# define SA 0
# define SB 1
# define SS 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RR 7
# define RRA 8
# define RRB 9
# define RRR 10

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

typedef struct s_medians
{
	int	values[DIVS - 1];
}	t_medians;

void	icq_init(t_icq *q);
void	icq_enfile(t_icq *q, int valeur, int reverse);
int		icq_defile(t_icq *q);
int		icq_tete(t_icq *q);
void	free_all(t_icq *q);

char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);

int		verif_all_nbr(char *str);
int		verif_format(char *str);
int		verif_list(int i, char **str);
int		verif_duplicates(t_icq *q);

void	sa(t_icq *a, t_icq *ops);
void	sb(t_icq *b, t_icq *ops);
void	ss(t_icq *a, t_icq *b, t_icq *ops);
void	pa(t_icq *a, t_icq *b, t_icq *ops);
void	pb(t_icq *a, t_icq *b, t_icq *ops);
void	ra(t_icq *a, t_icq *ops);
void	rb(t_icq *b, t_icq *ops);
void	rr(t_icq *a, t_icq *b, t_icq *ops);
void	rra(t_icq *a, t_icq *ops);
void	rrb(t_icq *b, t_icq *ops);
void	rrr(t_icq *a, t_icq *b, t_icq *ops);

void	pre_tri(t_icq *a, t_icq *b, t_medians *meds, t_icq *ops);
void	get_med_sorted(t_icq *q, t_medians *meds);
void	hidded_sort(t_icq *q);

void	sort(t_icq *q, t_icq *ops);

void	push_swap(t_icq *ops, t_icq *out);
void	simplify(t_icq *ops);
void	print_rules(int rule);

#endif
