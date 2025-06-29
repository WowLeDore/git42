/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:56 by pbona             #+#    #+#             */
/*   Updated: 2025/06/29 22:56:43 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(char *input, t_shell shell)
{
	if (shell.line.tokens)
		free(shell.line.tokens);
	if (input)
		free(input);
	exit(1);
}

const char	*token_type_to_str(t_token_type type)
{
	if (type == TOK_EMPTY) return "TOK_EMPTY";
	if (type == TOK_SINGLE_QUOTE) return "TOK_SINGLE_QUOTE";
	if (type == TOK_DOUBLE_QUOTE) return "TOK_DOUBLE_QUOTE";
	if (type == TOK_REDIRE_INPUT) return "TOK_REDIRE_INPUT";
	if (type == TOK_REDIRE_OUTPUT) return "TOK_REDIRE_OUTPUT";
	if (type == TOK_READ_DELIMITER) return "TOK_READ_DELIMITER";
	if (type == TOK_REDIRE_OUTPUT_APPEND) return "TOK_REDIRE_OUTPUT_APPEND";
	if (type == TOK_PIPE) return "TOK_PIPE";
	if (type == TOK_ENV_VAR) return "TOK_ENV_VAR";
	if (type == TOK_LAST_EXIT) return "TOK_LAST_EXIT";
	if (type == TOK_WORD) return "TOK_WORD";
	return "UNKNOWN";
}

void	print_token_list(t_token_list *lst)
{
	int	i = 0;

	printf("---- TOKEN LIST DEBUG ----\n");
	while (lst)
	{
		printf("Token %d:\n", i++);
		printf("  Type      : %s\n", token_type_to_str(lst->token));
		printf("  Word      : \"%.*s\"\n", lst->word_size, lst->word);
		printf("  Word Size : %d\n", lst->word_size);
		printf("  Prev      : %p\n", (void *)lst->prev);
		printf("  Curr      : %p\n", (void *)lst);
		printf("  Next      : %p\n\n", (void *)lst->next);
		lst = lst->next;
	}
	printf("--------------------------\n");
}


void	minishell(void)
{
	char			*input;
	static t_shell	shell;

	input = readline("mSh:~# ");
	while (input)
	{
		shell.line.tokens = lex(input);
		if (!shell.line.tokens)
			free_all(input, shell);
		//print_token_list(shell.line.tokens);
		free(input);
		input = readline("mSh:~# ");
	}
	printf("%s\n", "exit");
	exit(0);
}

int	main(int ac, char *av[])
{
	(void) av;
	if (ac != 1)
		return (0);
	minishell();
	return (0);
}
