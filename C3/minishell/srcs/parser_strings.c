/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:59:54 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/31 23:36:43 by mguillot         ###   ########.fr       */
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

void	space_split(char *str, size_t n, size_t *count)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (str[i] == ' ')
		{
			str[i] = 0;
			*count = *count + 1;
		}
		i++;
	}
}

size_t	copy_all_str(t_tree *ast, char *big_str, size_t i, size_t *count)
{
	t_token_list	*tmp;

	if (!ast)
		return (i);
	if (ast->type == N_TOKEN)
	{
		tmp = ast->node;
		ast->from = *count;
		while (tmp)
		{
			copy_word(big_str + i, tmp->type, tmp->word, tmp->size);
			if (tmp->type == T_ALL)
				space_split(big_str + i, tmp->size, count);
			i += tmp->size;
			tmp = tmp->next;
		}
		ast->to = *count;
		*count = *count + 1;
		big_str[i++] = '\0';
	}
	i = copy_all_str(ast->left, big_str, i, count);
	i = copy_all_str(ast->right, big_str, i, count);
	return (i);
}

size_t	str_len(t_tree *ast)
{
	t_token_list	*tmp;

	if (!ast)
		return (0);
	ast->len = 0;
	if (ast->type == N_TOKEN)
	{
		tmp = ast->node;
		while (tmp)
		{
			ast->len += tmp->size;
			tmp = tmp->next;
		}
		ast->len++;
	}
	ast->len += str_len(ast->left);
	ast->len += str_len(ast->right);
	return (ast->len);
}

int	group_str(t_shell *shell)
{
	str_len(shell->ast);
	if (!shell->ast || !shell->ast->len)
		return (0);
	shell->tot_str = malloc(sizeof(char) * shell->ast->len);
	if (!shell->tot_str)
		return (1);
	shell->str_nbr = 0;
	copy_all_str(shell->ast, shell->tot_str, 0, &shell->str_nbr);
	return (0);
}
