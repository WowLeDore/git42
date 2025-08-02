/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:56 by pbona             #+#    #+#             */
/*   Updated: 2025/08/02 17:56:57 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_t(t_token_list *tokens, size_t level)
{
	char	*type;
	char	*word;

	while (tokens)
	{
		type = (char *[]){[T_WORD] = "Word", [T_XWORD] = "Xword",
		[T_ALL] = "All", [T_VAR] = "Var", [T_VAL] = "Val", [N_PIPE] = "Pipe",
		[N_IN] = "In", [N_OUT] = "Out", [N_APPEND] = "Append",
		[N_HEREDOC] = "Heredoc", [N_TOKEN] = "Token"}[tokens->type];
		word = tokens->word;
		if (tokens->type == T_VAL)
			word = "123";
		printf("%*sid : |%-14p|, next_id : |%-14p|, size : |%-2ld|, type : |%-6"
			"s|, word : |%.*s|\n", (int) level * 2, "", tokens, tokens->next,
			tokens->size, type, (int)tokens->size, word);
		tokens = tokens->next;
	}
}

void	print_a(t_tree *ast, size_t level)
{
	const char			*type;

	if (!ast)
		return ;
	level++;
	type = "";
	if (ast->node)
		type = (char *[]){[T_WORD] = "Word", [T_XWORD] = "Xword",
		[T_ALL] = "All", [T_VAR] = "Var", [T_VAL] = "Val", [N_PIPE] = "Pipe",
		[N_IN] = "In", [N_OUT] = "Out", [N_APPEND] = "Append",
		[N_HEREDOC] = "Heredoc", [N_TOKEN] = "Token"}[ast->type];
	printf("%*s┌─[AST Node @%p]\n%*s├──Type   : %-6s\n%*s├──Depth  : %ld\n%*s├─"
		"─Len    : %ld\n%*s├──From   : %ld\n%*s├──To     : %ld\n%*s├──Tokens :"
		"\n", (int) level * 2, "", (void *) ast, (int) level * 2, "", type,
		(int) level * 2, "", level, (int) level * 2, "", ast->len,
		(int) level * 2, "", ast->from, (int) level * 2, "", ast->to,
		(int) level * 2, "");
	print_t(ast->node, level + 6);
	printf("%*s├─Left  of %p:\n", (int) level * 2, "", (void *) ast);
	print_a(ast->left, level);
	printf("%*s├─Right of %p:\n", (int) level * 2, "", (void *) ast);
	print_a(ast->right, level);
	printf("%*s└─\n", (int) level * 2, "");
}

void	print_str(char *str, size_t tot_len, size_t str_nbr)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (count < str_nbr && i < tot_len)
	{
		printf("String %02ld: |%s|\n", count + 1, &str[i]);
		i += ft_strlen(&str[i]) + 1;
		count++;
	}
}

void	reset_shell(t_shell *shell, unsigned char value)
{
	shell->input = readline("mSh:~# ");
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->tot_str = NULL;
	shell->str_nbr = 0;
	shell->value = value;
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	*shell;

	if (ac != 1 || !av)
		return (0);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		frexit(NULL, "Error in minishell");
	shell->env = copy_env(env);
	if (!shell->env)
		frexit(shell, "Error in copy_env");
	reset_shell(shell, 0);
	while (shell->input)
	{
		lexer(shell);
		print_t(shell->tokens, 0);
		parse(shell);
		print_a(shell->ast, 0);
		print_str(shell->tot_str, shell->ast->len, shell->str_nbr);
		frexit(shell, NULL);
		reset_shell(shell, shell->value);
	}
	frexit(shell, NULL);
	free_env(shell->env);
	free(shell);
	write(1, "exit\n", 5);
	exit(0);
}
