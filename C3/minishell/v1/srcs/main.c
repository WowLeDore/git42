/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:56 by pbona             #+#    #+#             */
/*   Updated: 2025/08/06 21:37:54 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_t(t_token_list *tokens)
{
	char	*type;
	char	*word;

	while (tokens)
	{
		type = (char *[]){[T_WORD] = "Word", [T_XWORD] = "Xword",
		[T_ALL] = "All", [T_VAR] = "Var", [T_VAL] = "Val", [T_PIPE] = "Pipe",
		[T_IN] = "In", [T_OUT] = "Out", [T_APPEND] = "Append",
		[T_HEREDOC] = "Heredoc"}[tokens->type];
		word = tokens->word;
		if (tokens->type == T_VAL)
			word = "123";
		printf("id : |%-14p|, next_id : |%-14p|, size : |%-2ld|, type : |%-6s|,"
			" word : |%.*s|\n", tokens, tokens->next, tokens->size, type,
			(int) tokens->size, word);
		tokens = tokens->next;
	}
}

void	print_str(char *str, size_t str_nbr)
{
	size_t	count;

	count = 0;
	while (count < str_nbr)
	{
		if (str && *str)
			printf("String %02ld:  |%p| |%s|\n", count, str, str);
		else
			printf("String %02ld:  |0x000000| ||\n", count);
		if (str && *str)
			str += ft_strlen(str) + 1;
		count++;
	}
}

void	print_commands(t_command_list *commands)
{
	size_t	i;
	char	**ptr;

	i = 0;
	if (commands)
		printf("\n");
	while (commands && commands[i].command)
	{
		printf("Command %02ld: |%s|\n   Options: ", i, commands[i].command);
		ptr = commands[i].options;
		while (ptr && *ptr)
			printf("|%s|, ", *ptr++);
		printf("0\n   In:      ");
		ptr = commands[i].read;
		while (ptr && *ptr)
			printf("|%s|, ", *ptr++);
		printf("0\n   Replace: ");
		ptr = commands[i].replace;
		while (ptr && *ptr)
			printf("|%s|, ", *ptr++);
		printf("0\n   Append:  ");
		ptr = commands[i].append;
		while (ptr && *ptr)
			printf("|%s|, ", *ptr++);
		printf("0\n   Heredoc: ");
		ptr = commands[i].heredoc;
		while (ptr && *ptr)
			printf("|%s|, ", *ptr++);
		printf("0\n");
		i++;
	}
	if (commands)
		printf("\n");
}

void	reset_shell(t_shell *shell, unsigned char value)
{
	shell->value = value;
	shell->input = readline("mSh:~# ");
	shell->tokens = NULL;
	shell->tot_str = NULL;
	shell->str_nbr = 0;
	shell->commands = NULL;
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	*shell;

	if (ac != 1 || !av)
		return (0);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		frexit(NULL, "Error in minishell");
	shell->env = copy_env(env, 0);
	if (!shell->env)
		frexit(shell, "Error in copy_env");
	reset_shell(shell, 0);
	while (shell->input)
	{
		lexer(shell);
		print_t(shell->tokens);
		parse(shell);
		print_str(shell->tot_str, shell->str_nbr);
		print_commands(shell->commands);
		frexit(shell, NULL);
		reset_shell(shell, shell->value);
	}
	frexit(shell, NULL);
	free_env(&shell->env);
	free(shell);
	write(1, "exit\n", 5);
	exit(0);
}
