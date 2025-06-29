/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:54:13 by mguillot          #+#    #+#             */
/*   Updated: 2025/06/29 23:47:34 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_word_size(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j]
		&& (ft_isalnum(str[i + j]) || str[i + j] == '_' || str[i + j] == '.'))
		j++;
	return (j);
}

int	add(t_token_list **token, t_token_type type, char *str, int *i)
{
	int				size;
	t_token_list	*tmp;

	tmp = malloc(sizeof(t_token_list));
	if (!tmp)
		return (1);
	if (*token)
		(*token)->next = tmp;
	tmp->prev = *token;
	tmp->token = type;
	tmp->word = str + *i;
	if (type == TOK_WORD)
		size = lex_word(str, i, *token, 0);
	else if (type == TOK_SINGLE_QUOTE)
		size = lex_word(str, i, *token, '\'');
	else if (type == TOK_DOUBLE_QUOTE)
		size = lex_word(str, i, *token, '"');
	else if (type == TOK_READ_DELIMITER || type == TOK_REDIRE_OUTPUT_APPEND
		|| type == TOK_LAST_EXIT)
		size = 2;
	else
		size = 1;
	tmp->word_size = size;
	*i = *i + size;
	*token = tmp;
	return (0);
}

t_token_list	*lex(char *str)
{
	t_token_list	*token;
	t_token_list	*head;
	int				err;
	int				i;

	i = 0;
	token = NULL;
	head = NULL;
	if (!*str)
	{
		head = malloc(sizeof(t_token_list));
		if (!head)
			return (NULL);
		head->token = TOK_EMPTY;
		head->word = "";
		head->word_size = 0;
		head->prev = NULL;
		head->next = NULL;
	}
	while (str[i])
	{
		if (str[i] < 33 || str[i] == 127)
			err = add(&token, TOK_EMPTY, str, &i);
		else if (str[i] == '\'')
			err = add(&token, TOK_SINGLE_QUOTE, str, &i);
		else if (str[i] == '"')
			err = add(&token, TOK_DOUBLE_QUOTE, str, &i);
		else if (str[i] == '<' && str[i + 1] != '<')
			err = add(&token, TOK_REDIRE_INPUT, str, &i);
		else if (str[i] == '>' && str[i + 1] != '>')
			err = add(&token, TOK_REDIRE_OUTPUT, str, &i);
		else if (str[i] == '<' && str[i + 1] == '<')
			err = add(&token, TOK_READ_DELIMITER, str, &i);
		else if (str[i] == '>' && str[i + 1] == '>')
			err = add(&token, TOK_REDIRE_OUTPUT_APPEND, str, &i);
		else if (str[i] == '|')
			err = add(&token, TOK_PIPE, str, &i);
		else if (str[i] == '$' && str[i + 1] != '?')
			err = add(&token, TOK_ENV_VAR, str, &i);
		else if (str[i] == '$' && str[i + 1] == '?')
			err = add(&token, TOK_LAST_EXIT, str, &i);
		else if (str[i] == '-')
			err = add(&token, TOK_OPTION, str, &i);
		else
			err = add(&token, TOK_WORD, str, &i);
		if (err)
			return (NULL);
		if (!head)
			head = token;
	}
	return (head);
}
