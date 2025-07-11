/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:56 by pbona             #+#    #+#             */
/*   Updated: 2025/07/11 15:23:53 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	frexit(char *err, t_shell *shell)
{
	t_token_list	*tmp;

	if (shell)
	{
		if (err)
			free(shell->input);
		while (shell->tokens)
		{
			tmp = shell->tokens->next;
			free(shell->tokens);
			shell->tokens = tmp;
		}
		if (err)
			free(shell);
	}
	if (err)
		write(2, err, ft_strlen(err));
	if (err)
		write(2, "\n", 1);
	if (err)
		exit(1);
}

void	print_t(t_token_list *tokens)
{
	char	*type;

	while (tokens)
	{
		if (tokens->type == T_WORD)
			type = "Word type token";
		else if (tokens->type == T_XWORD)
			type = "Xword type token";
		else if (tokens->type == T_ALL)
			type = "All type token";
		else if (tokens->type == T_VAR)
			type = "Var type token";
		else if (tokens->type == T_VAL)
			type = "Val type token";
		else if (tokens->type == T_SYM)
			type = "Symbol type token";
		else
			type = "Other type token";
		printf("id : |%-14p|, next_id : |%-14p|, size : |%-2ld|, type : |%-17s|"
			", group : |%-2ld|, word : |%.*s|\n", tokens, tokens->next,
			tokens->size, type, tokens->group, (int)tokens->size, tokens->word);
		tokens = tokens->next;
	}
}

void	print_a(t_tree *ast, size_t level)
{
	const char			*type;

	if (!ast)
		return ;
	type = (char *[]){[N_PIPE] = "Pipe node", [N_IN] = "In node",
	[N_OUT] = "Out node", [N_APPEND] = "Append node",
	[N_HEREDOC] = "Heredoc node", [N_TOKEN] = "Token node"}[ast->type];
	printf("%*s┌─[ AST Node @ %p ]\n%*s│ Type   : %-13s\n%*s│ Depth  : "
		"%ld\n%*s│ Tokens :\n%*s", (int) level * 2, "", (void *)ast,
		(int) level * 2, "", type, (int) level * 2, "", (long)level,
		(int) level * 2, "", (int) level * 2, "");
	print_t(ast->node);
	printf("\n");
	if (ast->left)
		printf("%*s│\n%*s├─ Left  of %p:\n%*s", (int) level * 2, "",
			(int) level * 2, "", (void *) ast, (int) level * 2, "");
	if (ast->left)
		print_a(ast->left, level + 1);
	if (ast->right)
		printf("%*s│\n%*s└─ Right of %p:\n%*s", (int) level * 2, "",
			(int) level * 2, "", (void *) ast, (int) level * 2, "");
	if (ast->right)
		print_a(ast->right, level + 1);
}

void	minishell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		frexit("Error in minishell", NULL);
	shell->env = env;
	shell->input = readline("mSh:~# ");
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->value = 0;
	while (shell->input)
	{
		lexer(shell);
		parse(shell);
		free(shell->input);
		shell->input = readline("mSh:~# ");
		frexit(NULL, shell);
		shell->tokens = NULL;
	}
	free(shell);
	printf("exit\n");
	exit(0);
}

int	main(int ac, char *av[], char *env[])
{
	(void) av;
	if (ac != 1)
		return (0);
	minishell(env);
	return (0);
}
