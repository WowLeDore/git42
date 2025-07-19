/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:59:54 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/17 19:44:50 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_word(char *dst, t_token type, char *src, size_t n)
{
	if (type != T_VAL)
		ft_memcpy(dst, src, n);
	else if (n == 1)
		*(dst + 0) = (((unsigned char) *src) % 10) + '0';
	else if (n == 2)
	{
		*(dst + 0) = ((((unsigned char) *src) / 10) % 10) + '0';
		*(dst + 1) = (((unsigned char) *src) % 10) + '0';
	}
	else if (n == 3)
	{
		*(dst + 0) = (((unsigned char) *src) / 100) + '0';
		*(dst + 1) = ((((unsigned char) *src) / 10) % 10) + '0';
		*(dst + 2) = (((unsigned char) *src) % 10) + '0';
	}
}

size_t	copy_all_str(t_tree *ast, char *big_str, size_t i)
{
	t_token_list	*tmp;
	size_t			last_group;

	if (!ast)
		return (i);
	if (ast->type == N_TOKEN)
	{
		tmp = ast->node;
		last_group = 0;
		while (tmp)
		{
			if (tmp->group != last_group || (!tmp->group && big_str[i]))
				big_str[i++] = '\0';
			copy_word(big_str + i, tmp->type, tmp->word, tmp->size);
			i += tmp->size;
			last_group = tmp->group;
			tmp = tmp->next;
		}
		big_str[i++] = '\0';
	}
	i = copy_all_str(ast->left, big_str, i);
	i = copy_all_str(ast->right, big_str, i);
	return (i);
}

size_t	str_len(t_tree *ast)
{
	t_token_list	*tmp;
	size_t			last_group;

	if (!ast)
		return (0);
	ast->len = 0;
	if (ast->type == N_TOKEN)
	{
		tmp = ast->node;
		last_group = 0;
		while (tmp)
		{
			if (last_group != tmp->group || !tmp->group)
				ast->len++;
			ast->len += tmp->size;
			last_group = tmp->group;
			tmp = tmp->next;
		}
	}
	ast->len += str_len(ast->left);
	ast->len += str_len(ast->right);
	return (ast->len);
}

int	group_str(t_shell *shell)
{
	str_len(shell->ast);
	shell->tot_str = NULL;
	if (!shell->ast || !shell->ast->len)
		return (0);
	shell->tot_str = malloc(sizeof(char) * shell->ast->len);
	if (!shell->tot_str)
		return (1);
	copy_all_str(shell->ast, shell->tot_str, 0);
	return (0);
}
