/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:13:15 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/09 19:00:04 by mguillot         ###   ########.fr       */
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
	return ("UNKNOWN");
}

void	print_token(t_command *cmd, t_token *token)
{
	if (!token)
	{
		printf("       " RED "Token: NULL" RESET "\n");
		return ;
	}
	printf("       " BOLD "Token:" RESET " %s%s" RESET " (idx: %zu, size: %zu, "
		"content: \"%.*s\")\n", get_type_color(token->type),
		get_type_name(token->type), token->indx, token->size, (int) token->size,
		cmd->word + token->indx);
}

void	print_command(t_command *cmd)
{
	t_token	*token;

	if (!cmd)
	{
		printf("   " RED "Command: NULL" RESET "\n");
		return ;
	}
	printf("   " BOLD "Command:" RESET " \"%s\"\n", cmd->word);
	token = cmd->toks;
	while (token)
	{
		print_token(cmd, token);
		token = token->next;
	}
}

void	print_minishell(t_minishell *ms)
{
	t_command	*cmd;
	size_t		cmd_num;

	if (!ms)
	{
		printf(RED "MiniShell: NULL" RESET "\n");
		return ;
	}
	printf(BOLD CYAN "MiniShell Structure" RESET "\n");
	printf("================================\n");
	cmd = ms->coms;
	cmd_num = 1;
	while (cmd)
	{
		printf(BOLD YELLOW "Command #%ld" RESET "\n", cmd_num++);
		print_command(cmd);
		printf("--------------------------------\n");
		cmd = cmd->next;
	}
}
