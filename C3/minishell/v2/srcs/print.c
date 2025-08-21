/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:13:15 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/18 15:22:03 by mguillot         ###   ########.fr       */
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
	if (type == NONTYPE)
		return (BOLD RED);
	if (type == META)
		return (RED);
	if (type == DQUOTE)
		return (GREEN);
	if (type == SQUOTE)
		return (YELLOW);
	if (type == IN)
		return (RED);
	if (type == OUT)
		return (GREEN);
	if (type == HEREDOC)
		return (YELLOW);
	if (type == APPEND)
		return (BLUE);
	if (type == WORDS)
		return (MAGENTA);
	if (type == XPNDED)
		return (CYAN);
	return (WHITE);
}

const char	*get_type_name(t_type type)
{
	if (type == NONTYPE)
		return ("NONTYPE");
	if (type == META)
		return ("META");
	if (type == DQUOTE)
		return ("DOUBLE QUOTE");
	if (type == SQUOTE)
		return ("SIMPLE QUOTE");
	if (type == IN)
		return ("IN");
	if (type == OUT)
		return ("OUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == APPEND)
		return ("APPEND");
	if (type == WORDS)
		return ("WORDS");
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

void	print_pipe(t_pipe *pipe)
{
	t_token	*token;

	if (!pipe)
	{
		printf("   " RED "Pipe: NULL" RESET "\n");
		return ;
	}
	printf("   " BOLD "Pipe:" RESET " \"%s\"\n", pipe->word);
	token = pipe->toks;
	while (token)
	{
		print_token(token);
		token = token->next;
	}
}

void	print_comm(t_comm *comm)
{
	size_t	i;

	if (!comm)
	{
		printf("   " RED "Command: NULL" RESET "\n");
		return ;
	}
	printf("   " BOLD "Command:" RESET " \"%s\"\n", comm->word);
	if (comm->options)
	{
		printf("      " CYAN "Options:" RESET "\n");
		i = 0;
		while (comm->options[i])
			printf("         - |%s|\n", comm->options[i++]);
	}
	if (comm->ins)
	{
		printf("      " RED "Inputs:" RESET "\n");
		i = 0;
		while (comm->ins[i])
			printf("         < |%s|\n", comm->ins[i++]);
	}
	if (comm->outs)
	{
		printf("      " GREEN "Outputs:" RESET "\n");
		i = 0;
		while (comm->outs[i])
			printf("         > |%s|\n", comm->outs[i++]);
	}
	if (comm->appends)
	{
		printf("      " BLUE "Appends:" RESET "\n");
		i = 0;
		while (comm->appends[i])
			printf("         >> |%s|\n", comm->appends[i++]);
	}
	if (comm->heredoc)
		printf("      " YELLOW "Heredoc:" RESET "\n         << |%s|\n",
			comm->heredoc);
}

void	print_big_str(char *big_str)
{
	char	*ptr;
	size_t	i;

	if (!big_str)
	{
		printf(RED "Big string: NULL" RESET "\n");
		return ;
	}
	printf(BOLD MAGENTA "Big string parts:" RESET "\n");
	ptr = big_str;
	i = 0;
	while (*ptr)
	{
		printf("   [%zu]: \"%s\"\n", i++, ptr);
		ptr += ft_strlen(ptr) + 1;
	}
}

void	print_minishell_extended(t_minishell *shell)
{
	t_comm	*comm;
	size_t	count;

	printf(BOLD CYAN "MiniShell Extended Structure" RESET "\n");
	printf("================================\n");
	if (shell->value)
		printf(BOLD "Value:" RESET " \"%s\"\n", shell->value);
	if (shell->input)
		printf(BOLD "Input:" RESET " \"%s\"\n", shell->input);
	if (shell->big_str)
		print_big_str(shell->big_str);
	if (shell->comms)
	{
		printf(BOLD YELLOW "Commands:" RESET "\n");
		comm = shell->comms;
		count = 1;
		while (comm)
		{
			printf(BOLD "Command #%ld" RESET "\n", count++);
			print_comm(comm);
			printf("   --------------------------------\n");
			comm = comm->next;
		}
	}
	printf("================================\n");
}

void	print_minishell(t_minishell *shell)
{
	t_pipe	*pipe;
	size_t	count;

	if (!shell)
		printf(RED "MiniShell: NULL" RESET "\n");
	if (!shell)
		return ;
	printf(BOLD CYAN "MiniShell Structure" RESET "\n");
	printf("================================\n");
	pipe = shell->pipes;
	count = 1;
	while (pipe)
	{
		printf(BOLD YELLOW "Pipe #%ld" RESET "\n", count++);
		print_pipe(pipe);
		printf("--------------------------------\n");
		pipe = pipe->next;
	}
	print_minishell_extended(shell);
}
