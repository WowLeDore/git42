/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:29:38 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/08 23:09:55 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token
{
	T_XWORD,
	T_WORD,
	T_ALL,
	T_VAR,
	T_VAL,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token;

typedef struct s_token_list
{
	struct s_token_list	*next;
	char				*word;
	size_t				size;
	t_token				type;
}	t_token_list;

typedef struct s_command_list
{
	char	*command;
	char	**options;
	char	**read;
	char	**replace;
	char	**append;
	char	**heredoc;
}	t_command_list;

typedef struct s_shell
{
	char			**env;
	unsigned char	value;
	char			*input;
	t_token_list	*tokens;
	char			*tot_str;
	size_t			str_nbr;
	t_command_list	*commands;
}	t_shell;

#endif