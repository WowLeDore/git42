/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:29:49 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/02 16:14:37 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token_list *head)
{
	t_token_list	*tmp;

	while (head)
	{
		tmp = head->next;
		head->next = NULL;
		free(head);
		head = NULL;
		head = tmp;
	}
}

void	free_ast(t_tree *ast)
{
	if (!ast)
		return ;
	free_tokens(ast->node);
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
	ast = NULL;
}

void	free_env(char **env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	env = NULL;
}

void	frexit(t_shell *shell, char *err_msg)
{
	if (!shell)
	{
		if (err_msg)
		{
			write(2, err_msg, ft_strlen(err_msg));
			write(2, "\n", 1);
			exit(1);
		}
		return ;
	}
	if (shell->input)
		free(shell->input);
	if (!shell->ast)
		free_tokens(shell->tokens);
	free_ast(shell->ast);
	if (shell->tot_str)
		free(shell->tot_str);
	if (err_msg)
	{
		free_env(shell->env);
		free(shell);
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
		exit(1);
	}
}
