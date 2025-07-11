/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:48:48 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/11 10:56:13 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_sym(char **str_l, size_t *len_l, char *str, size_t len)
{
	size_t	i;

	i = 0;
	str_l[0] = NULL;
	str_l[1] = NULL;
	len_l[0] = 0;
	len_l[1] = 0;
	while (i < len)
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			str_l[0] = str + i;
			len_l[0] = 1 + (str[i] == str[i + 1]);
			if (i + len_l[0] >= len)
				break ;
			str_l[1] = str + i + len_l[0];
			len_l[1] = len - i - len_l[0];
			break ;
		}
		i++;
	}
}

int	make(t_token_list **head, char	**str, size_t *len, int sym)
{
	t_token_list	*token;

	if (!str[sym])
		return (0);
	token = malloc(sizeof(t_token_list));
	if (!token)
		return (1);
	token->next = (*head)->next;
	token->word = str[sym];
	token->size = len[sym];
	token->type = T_ALL;
	if (!sym)
		token->type = T_SYM;
	token->group = 0;
	(*head)->next = token;
	return (0);
}

int	lex_split(t_token_list **head)
{
	char			*sym_str_list[2];
	size_t			sym_len_list[2];
	t_token_list	**tmp;

	tmp = head;
	while (*tmp)
	{
		if ((*tmp)->type == T_ALL)
		{
			find_sym(sym_str_list, sym_len_list, (*tmp)->word, (*tmp)->size);
			(*tmp)->size -= sym_len_list[0] + sym_len_list[1];
			if (make(tmp, sym_str_list, sym_len_list, 1)
				|| make(tmp, sym_str_list, sym_len_list, 0))
				return (1);
		}
		tmp = &(*tmp)->next;
	}
	return (0);
}
