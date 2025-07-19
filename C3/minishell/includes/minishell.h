/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:27:49 by pbona             #+#    #+#             */
/*   Updated: 2025/07/17 19:43:12 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf/ft_printf.h"
# include "ft_get_next_line/get_next_line.h"

# include "tokens.h"

# include <stdio.h>
# include <readline/readline.h>

/*structures*/
typedef struct s_shell
{
	char			**env;
	char			*input;
	t_token_list	*tokens;
	t_tree			*ast;
	unsigned char	value;
	char			*tot_str;
}	t_shell;

/*fonctions*/
void	lexer(t_shell *shell);
void	parse(t_shell *shell);
void	frexit(char *err, t_shell *shell);
void	print_t(t_token_list *tokens, size_t level);
void	print_a(t_tree *ast, size_t level);
int		lex_quote(t_token_list **head, char *str);
int		mak_expnd(t_token_list	**head);
void	lex_expnd(t_token_list *tokens, char **env, unsigned char value);
int		lex_split(t_token_list **head);
int		group_str(t_shell *shell);

#endif
