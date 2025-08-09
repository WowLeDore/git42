/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:35 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/09 19:24:27 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>

typedef enum e_type
{
	NONTYPE,
	WORDS,
	COMMAND,
	OPTION,
	META,
	HEREDOC,
	APPEND,
	IN,
	OUT
}	t_type;

typedef struct s_token
{
	struct s_token	*next;
	t_type			type;
	size_t			indx;
	size_t			size;
}	t_token;

typedef struct s_command
{
	struct s_command	*next;
	char				*word;
	t_token				*toks;
}	t_command;

typedef struct s_minishell
{
	t_command	*coms;
}	t_minishell;

int		init_coms(t_command *coms, char *str);
int		spliter(t_command *coms);
void	group_operators(t_minishell *shell);
void	remove_meta(t_minishell *shell);
void	group_redirections(t_minishell *shell);
void	print_minishell(t_minishell *shell);
int		parser(char *str, t_minishell *shell);

#endif
