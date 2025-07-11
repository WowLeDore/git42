/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:12:39 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/11 14:27:05 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cut(t_token_list *prev, t_token_list *tmp)
{
	t_token_list	*tok;

	tok = prev;
	while (tok->next != tmp)
		tok = tok->next;
	tok->next = NULL;
}

int	tree_pipes(t_tree **ast, t_token_list *tok)
{
	t_token_list	*tmp;
	t_token_list	*prev;

	prev = tok;
	tmp = tok;
	*ast = malloc(sizeof(t_tree));
	if (!*ast)
		return (1);
	while (tmp)
	{
		if (tmp->type == T_SYM && *tmp->word == '|')
		{
			cut(prev, tmp);
			(*ast)->type = N_PIPE;
			(*ast)->node = tmp;
			(*ast)->left = NULL;
			if (prev && tree_pipes(&(*ast)->left, prev))
				return (1);
			(*ast)->right = NULL;
			if (tmp->next && tree_pipes(&(*ast)->right, tmp->next))
				return (1);
			prev = tmp->next;
			tmp->next = NULL;
			tmp = prev;
			return (0);
		}
		else
			tmp = tmp->next;
	}
	(*ast)->type = N_TOKEN;
	(*ast)->node = tok;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	return (0);
}

void	parse(t_shell *shell)
{
	if (tree_pipes(&shell->ast, shell->tokens))
		frexit("Error in tree_pipes", shell);
	print_a(shell->ast, 0);
}
