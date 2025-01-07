/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:39:12 by mguillot          #+#    #+#             */
/*   Updated: 2024/09/01 23:39:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAIN_H
# define FT_MAIN_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_number
{
	char	*nb_int;
	char	*nb_str;
}			t_number;

void			ft_putstr(char *str);
bool			ft_isprintable(char c);
bool			ft_iscolon(char c);
bool			ft_isnum(char c);
void			ft_init_tab(int tab[4]);
int				ft_strlen(char *str);
char			*ft_strndup(char *src, int n);
int				ft_strcmp(char *str1, char *str2);
void			ft_print_nbr(char *nbr, struct s_number *dict);
void			ft_print_nbr_1(char *nbr, struct s_number *dict);
int				ft_arraylen(char **nbrs);
void			ft_print_whole_nb(char **nbrs, struct s_number *dict);
struct s_number	*ft_parse_file(char *file);
void			ft_parse_line(struct s_number *num, char *file, int *i);
char			*ft_ten_pow(int n);
bool			ft_verif_dict(char *dict);
char			*get_file(char *dict_name);
int				ft_len_file(char *file);

#endif