/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:35 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/13 16:55:18 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdlib.h>
# include <stdio.h>

typedef enum e_type
{
	NONTYPE,
	WORDS,
	DQUOTE,
	SQUOTE,
	XPNDED,
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
	size_t			size;
	char			*word;
	struct s_token	*subs;
}	t_token;

typedef struct s_pipe
{
	struct s_pipe	*next;
	char			*word;
	t_token			*toks;
}	t_pipe;

typedef struct s_minishell
{
	t_pipe	*pipes;
	char	*value;
	char	**env;
}	t_minishell;

int		free_all(t_minishell *shell, int value);
int		init_pipe(t_pipe *pipe, char *str);
int		init_toks(t_token **toks);
int		spliter(t_pipe *pipes);
void	group_operators(t_minishell *shell);
void	remove_meta(t_minishell *shell);
void	group_redirections(t_minishell *shell);
int		handle_quote(int quote, char c);
int		sub_quote(t_minishell *shell);
int		expand_vars(t_minishell	*shell);
char	**copy_env(char **env, size_t	add);
char	*get_env(char **env, char *key, size_t len);
int		change_env(char **env, char *key, size_t key_len, char *value);
int		add_env(char ***env, char *key, size_t key_len, char *value);
int		remove_env(char	***env, char *key, size_t key_len);
void	free_env(char ***env);
void	print_minishell(t_minishell *shell);
int		parser(t_minishell *shell, char *str);

#endif
