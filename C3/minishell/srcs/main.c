/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:56 by pbona             #+#    #+#             */
/*   Updated: 2025/07/17 19:45:10 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t(t_tree *ast)
{
	t_token_list	*tmp;

	if (!ast)
		return ;
	while (ast->node)
	{
		tmp = ast->node->next;
		free(ast->node);
		ast->node = tmp;
	}
	free_t(ast->left);
	free_t(ast->right);
	free(ast);
}

void	frexit(char *err, t_shell *shell)
{
	if (shell)
		free_t(shell->ast);
	if (shell)
		free(shell->input);
	if (shell)
		free(shell->tot_str);
	if (!err)
		return ;
	else if (shell)
		free(shell);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit(1);
}

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
			"s|, group : |%-2ld|, word : |%.*s|\n", (int) level * 2, "",
			tokens, tokens->next, tokens->size, type, tokens->group,
			(int)tokens->size, word);
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
		"─Len    : %ld\n%*s├──Tokens :\n", (int) level * 2, "", (void *) ast,
		(int) level * 2, "", type, (int) level * 2, "", level, (int) level * 2,
		"", ast->len, (int) level * 2, "");
	print_t(ast->node, level + 6);
	printf("%*s├─Left  of %p:\n", (int) level * 2, "", (void *) ast);
	print_a(ast->left, level);
	printf("%*s├─Right of %p:\n", (int) level * 2, "", (void *) ast);
	print_a(ast->right, level);
	printf("%*s└─\n", (int) level * 2, "");
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	*shell;

	if (ac != 1 || !av)
		return (0);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		frexit("Error in minishell", NULL);
	shell->env = env;
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->value = 0;
	shell->input = readline("mSh:~# ");
	while (shell->input)
	{
		lexer(shell);
		parse(shell);
		frexit(NULL, shell);
		shell->tokens = NULL;
		shell->ast = NULL;
		shell->input = readline("mSh:~# ");
	}
	frexit(NULL, shell);
	free(shell);
	printf("exit\n");
	exit(0);
}
