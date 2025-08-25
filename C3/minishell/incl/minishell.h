/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:35 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/25 17:44:24 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


typedef enum e_type
{
	SQUOTE,
	DQUOTE,
	NONTYPE,
	WORDS,
	XPNDED,
	META,
	HEREDOC,
	APPEND,
	IN,
	OUT
}	t_type;

typedef struct s_token
{
	struct s_token	*next;
	size_t			size;
	char			*word;
	struct s_token	*subs;
	t_type			type;
	char			*heredoc;
}	t_token;

typedef struct s_pipe
{
	struct s_pipe	*next;
	char			*word;
	t_token			*toks;
}	t_pipe;

typedef struct s_comm
{
	struct s_comm	*next;
	char			*word;
	char			**options;
	char			**ins;
	char			**outs;
	char			**appends;
	char			*heredoc;
	int				builtin;
}	t_comm;

typedef struct s_minishell
{
	char	*value;
	char	**env;
	char	*input;
	t_pipe	*pipes;
	char	*big_str;
	t_comm	*comms;
	size_t	heredoc;
}	t_minishell;

void	frexit(t_minishell *shell, char *err_msg, int value);
void	free_env(char ***env);
void	free_tok(t_token *tok);

char	**copy_env(char **env, size_t	add);
char	*get_env(char **env, char *key, size_t len);
int		change_env(char **env, char *key, size_t key_len, char *value);
int		add_env(char ***env, char *key, size_t key_len, char *value);
int		remove_env(char	***env, char *key, size_t key_len);

int		init_pipe(t_pipe *pipe, char *str);
int		init_toks(t_token **toks);
int		spliter(t_pipe *pipes);
int		checker(t_minishell *shell);
void	clean(t_minishell *shell);
void	group_operators(t_minishell *shell);
void	remove_meta(t_minishell *shell);
void	group_redirections(t_minishell *shell);
int		handle_quote(int quote, char c);
int		sub_quote(t_minishell *shell);
int		expand_vars(t_minishell	*shell);
int		word_split(t_minishell *shell);
int		heredoc(t_minishell *shell);
size_t	big_len(t_minishell *shell);
void	big_copy(t_minishell *shell);
char	*assign_comms(t_token *tok, t_comm *comm, char *ptr);
int		make_commands(t_minishell *shell);
int		parser(t_minishell *shell);

int		exec(t_minishell *shell);

int		b_echo(char **argv);

void	print_minishell(t_minishell *shell);

#endif
