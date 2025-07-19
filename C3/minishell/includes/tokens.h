/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:29:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/17 15:07:40 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum u_token
{
	T_XWORD,
	T_WORD,
	T_ALL,
	T_VAR,
	T_VAL,
	N_PIPE,
	N_IN,
	N_OUT,
	N_APPEND,
	N_HEREDOC,
	N_TOKEN
}	t_token;

typedef struct s_token_list
{
	struct s_token_list	*next;
	char				*word;
	size_t				size;
	t_token				type;
	size_t				group;
}	t_token_list;

typedef struct s_tree
{
	t_token			type;
	t_token_list	*node;
	struct s_tree	*left;
	struct s_tree	*right;
	size_t			len;
}	t_tree;

#endif