/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:27:49 by pbona             #+#    #+#             */
/*   Updated: 2025/08/02 19:32:21 by mguillot         ###   ########.fr       */
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
# include <unistd.h>

/*structures*/
typedef struct s_shell
{
	char			**env;
	char			*input;
	t_token_list	*tokens;
	t_tree			*ast;
	char			*tot_str;
	size_t			str_nbr;
	unsigned char	value;
}	t_shell;

/*fonctions*/
void	frexit(t_shell *shell, char *err_msg);
char	**copy_env(char **env);
void	reset_shell(t_shell *shell, unsigned char value);
void	lexer(t_shell *shell);
int		lex_quote(t_token_list **head, char *str);
char	*first_char(char *str, size_t len, char c1, char c2);
int		mak_expnd(t_token_list	**head);
void	lex_expnd(t_token_list *tokens, char **env, unsigned char value);
int		lex_split(t_token_list **head);
void	parse(t_shell *shell);
int		group_str(t_shell *shell);
void	free_env(char **env);

/*commandes*/
int		echo(int argc, char **argv);

#endif
