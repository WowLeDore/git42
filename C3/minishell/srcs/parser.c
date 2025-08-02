/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:00:04 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/02 15:32:42 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_tree(t_tree *ast, t_token type, t_token_list *node)
{
	ast->type = type;
	ast->node = node;
	ast->left = NULL;
	ast->right = NULL;
	ast->len = 0;
	ast->from = 0;
	ast->to = 0;
}

t_tree	*tree_sym(t_token_list *tok, t_token sym)
{
	t_token_list	*token;
	t_token_list	*tmp;
	t_tree			*ast;

	tmp = tok;
	ast = malloc(sizeof(t_tree));
	if (!ast)
		return (NULL);
	while (tmp)
	{
		if (tmp->type == sym)
		{
			token = tok;
			while (token && token->next != tmp)
				token = token->next;
			if (token)
				token->next = NULL;
			make_tree(ast, sym, tmp);
			return (ast);
		}
		tmp = tmp->next;
	}
	make_tree(ast, N_TOKEN, tok);
	return (ast);
}

int	free_all(t_tree *left, t_tree *new, int ret)
{
	if (left)
		free(left);
	if (new)
		free(new);
	return (ret);
}

int	in_cut(t_tree *ast, t_token sym)
{
	t_tree	*new;

	if (!ast)
		return (0);
	if (ast->type != N_TOKEN)
		return (in_cut(ast->left, sym) || in_cut(ast->right, sym));
	new = tree_sym(ast->node, sym);
	if (new->type == N_TOKEN)
		return (free_all(NULL, new, 0));
	if (ast->node != new->node)
		new->left = malloc(sizeof(t_tree));
	if (ast->node != new->node && !new->left)
		return (free_all(NULL, new, 1));
	if (ast->node != new->node)
		make_tree(new->left, N_TOKEN, ast->node);
	if (new->node->next)
		new->right = malloc(sizeof(t_tree));
	if (new->node->next && !new->right)
		return (free_all(new->left, new, 1));
	if (new->node->next)
		make_tree(new->right, N_TOKEN, new->node->next);
	new->node->next = NULL;
	*ast = *new;
	free(new);
	return (in_cut(ast->left, sym) || in_cut(ast->right, sym));
}

void	parse(t_shell *shell)
{
	shell->ast = malloc(sizeof(t_tree));
	if (!shell->ast)
		frexit(shell, "Error in parse");
	make_tree(shell->ast, N_TOKEN, shell->tokens);
	if (in_cut(shell->ast, N_PIPE)
		|| in_cut(shell->ast, N_OUT)
		|| in_cut(shell->ast, N_IN)
		|| in_cut(shell->ast, N_APPEND)
		|| in_cut(shell->ast, N_HEREDOC))
		frexit(shell, "Error in in_cut");
	if (group_str(shell))
		frexit(shell, "Error in group_str");
}
