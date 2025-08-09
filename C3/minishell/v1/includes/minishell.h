/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:27:49 by pbona             #+#    #+#             */
/*   Updated: 2025/08/05 19:08:06 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf/ft_printf.h"
# include "ft_get_next_line/get_next_line.h"

# include "structures.h"

# include <stdio.h>
# include <readline/readline.h>

/*fonctions*/
char	**copy_env(char **env, size_t	add);
char	*get_env(char **env, char *key, size_t len);
int		change_env(char **env, char *key, size_t key_len, char *value);
int		add_env(char ***env, char *key, size_t key_len, char *value);
int		remove_env(char	***env, char *key, size_t key_len);
void	free_env(char ***env);
void	frexit(t_shell *shell, char *err_msg);
void	reset_shell(t_shell *shell, unsigned char value);
void	lexer(t_shell *shell);
int		lex_quote(t_token_list **head, char *str);
int		mak_expnd(t_token_list	**head);
void	lex_expnd(t_token_list *tokens, char **env, unsigned char value);
int		lex_split(t_token_list **head);
char	*first_char(char *str, size_t len, char c1, char c2);
void	parse(t_shell *shell);
size_t	command_count(t_token_list *tokens);
void	assign_commands(t_command_list *c, t_token_list *t, char *s, size_t n);
int		make_options(t_command_list *commands, t_token_list *tok, char *str);

/*commandes*/
int		echo(int argc, char **argv);

#endif
