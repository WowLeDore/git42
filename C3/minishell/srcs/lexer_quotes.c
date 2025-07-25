/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:47:27 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/11 13:48:04 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_list	*lex_all(char c, char **p)
{
	char			*end;
	t_token_list	*all;

	all = malloc(sizeof(t_token_list));
	if (!all)
		return (NULL);
	end = ft_strchr(*p, c);
	all->next = NULL;
	all->word = *p;
	if (!end)
		all->size = 0;
	else
		all->size = end - *p;
	all->type = T_ALL;
	all->group = 0;
	if (!end)
		*p += all->size;
	else
		*p = end;
	return (all);
}

t_token_list	*lex_quote_c(char c, char **p)
{
	char			*end;
	t_token_list	*quote;

	quote = malloc(sizeof(t_token_list));
	if (!quote)
		return (NULL);
	end = ft_strchr(*p + 1, c);
	if (!end)
		end = *p;
	quote->next = NULL;
	quote->word = *p + 1;
	quote->size = 0;
	if (end >= *p + 1)
		quote->size = end - *p - 1;
	quote->type = T_WORD;
	if (c == '"')
		quote->type = T_XWORD;
	quote->group = 0;
	*p = end + 1;
	return (quote);
}

char	first_quote(char *str)
{
	char	*simple_quote;
	char	*double_quote;

	simple_quote = ft_strchr(str, '\'');
	double_quote = ft_strchr(str, '"');
	if (simple_quote && double_quote && simple_quote < double_quote)
		return ('\'');
	if (simple_quote && double_quote && simple_quote > double_quote)
		return ('"');
	if (simple_quote)
		return ('\'');
	if (double_quote)
		return ('"');
	return ('\0');
}

int	lex_quote(t_token_list **head, char *str)
{
	t_token_list	*last;

	last = lex_all(first_quote(str), &str);
	if (!last)
		return (1);
	*head = last;
	while (*str)
	{
		last->next = lex_quote_c(first_quote(str), &str);
		last = last->next;
		if (!last)
			return (1);
		last->next = lex_all(first_quote(str), &str);
		last = last->next;
		if (!last)
			return (1);
	}
	return (0);
}
