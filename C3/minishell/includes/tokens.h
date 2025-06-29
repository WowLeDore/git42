/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:29:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/29 22:54:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_token_type
{
	TOK_EMPTY,
	TOK_WORD,
	TOK_SINGLE_QUOTE,
	TOK_DOUBLE_QUOTE,
	TOK_REDIRE_INPUT,
	TOK_REDIRE_OUTPUT,
	TOK_READ_DELIMITER,
	TOK_REDIRE_OUTPUT_APPEND,
	TOK_PIPE,
	TOK_ENV_VAR,
	TOK_LAST_EXIT,
	TOK_OPTION
}	t_token_type;

typedef struct s_token_list
{
	t_token_type		token;
	char				*word;
	int					word_size;
	struct s_token_list	*prev;
	struct s_token_list	*next;
}	t_token_list;

#endif