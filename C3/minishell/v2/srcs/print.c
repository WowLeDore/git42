/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:13:15 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/13 16:53:24 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define BOLD	"\033[1m"

const char	*get_type_color(t_type type)
{
	if (type == IN)
		return (CYAN);
	if (type == OUT)
		return (BLUE);
	if (type == HEREDOC)
		return (RED);
	if (type == APPEND)
		return (MAGENTA);
	if (type == META)
		return (YELLOW);
	if (type == WORDS)
		return (GREEN);
	if (type == COMMAND)
		return (BOLD GREEN);
	if (type == OPTION)
		return (YELLOW);
	if (type == DQUOTE)
		return (BLUE);
	if (type == SQUOTE)
		return (BOLD BLUE);
	if (type == XPNDED)
		return (BOLD MAGENTA);
	return (WHITE);
}

const char	*get_type_name(t_type type)
{
	if (type == NONTYPE)
		return ("NONTYPE");
	if (type == IN)
		return ("IN");
	if (type == OUT)
		return ("OUT");
	if (type == META)
		return ("META");
	if (type == WORDS)
		return ("WORDS");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == APPEND)
		return ("APPEND");
	if (type == COMMAND)
		return ("COMMAND");
	if (type == OPTION)
		return ("OPTION");
	if (type == DQUOTE)
		return ("DOUBLE QUOTE");
	if (type == SQUOTE)
		return ("SIMPLE QUOTE");
	if (type == XPNDED)
		return ("EXPANDED VARIABLE");
	return ("UNKNOWN");
}

void	print_token(t_token *token)
{
	char	*word;
	char	*space;
	t_token	*subs;

	if (!token)
	{
		printf("       " RED "Token: NULL" RESET "\n");
		return ;
	}
	if (token->word && *token->word)
		word = token->word;
	else
		word = "";
	space = "       ";
	if (token->subs)
		space = "   ";
	printf("%s" BOLD "Token:" RESET " %s%s" RESET " (size: %zu, content: "
		"\"%.*s\")\n", space, get_type_color(token->type),
		get_type_name(token->type), token->size, (int) token->size, word);
	subs = token->subs;
	while (subs)
	{
		print_token(subs);
		subs = subs->next;
	}
}

void	print_command(t_pipe *pipe)
{
	t_token	*token;

	if (!pipe)
	{
		printf("   " RED "Command: NULL" RESET "\n");
		return ;
	}
	printf("   " BOLD "Command:" RESET " \"%s\"\n", pipe->word);
	token = pipe->toks;
	while (token)
	{
		print_token(token);
		token = token->next;
	}
}

void	print_minishell(t_minishell *shell)
{
	t_pipe	*pipe;
	size_t	pipe_num;

	if (!shell)
	{
		printf(RED "MiniShell: NULL" RESET "\n");
		return ;
	}
	printf(BOLD CYAN "MiniShell Structure" RESET "\n");
	printf("================================\n");
	pipe = shell->pipes;
	pipe_num = 1;
	while (pipe)
	{
		printf(BOLD YELLOW "Command #%ld" RESET "\n", pipe_num++);
		print_command(pipe);
		printf("--------------------------------\n");
		pipe = pipe->next;
	}
}
