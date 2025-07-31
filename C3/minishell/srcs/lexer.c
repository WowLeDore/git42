/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:34:56 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/01 01:04:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_list	*rem_space(t_token_list *head)
{
	t_token_list	*token;

	token = malloc(sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->word = ft_memrchr(head->word, ' ', head->size) + 1;
	token->size = head->size - (token->word - head->word);
	head->size = token->word - head->word;
	token->next = head->next;
	token->type = T_ALL;
	head->next = token;
	return (token);
}

void	lex_clean(t_token_list **head)
{
	t_token_list	**tmp;
	t_token_list	*to_free;
	size_t			i;

	tmp = head;
	while (*tmp)
	{
		i = 0;
		while ((*tmp)->type == T_ALL && i < (*tmp)->size
			&& (*tmp)->word[i] == ' ')
			i++;
		if (i == (*tmp)->size || (*tmp)->size < 1)
		{
			to_free = *tmp;
			*tmp = (*tmp)->next;
			free(to_free);
		}
		else
			tmp = &(*tmp)->next;
	}
}

void	lex_trims(t_token_list **head)
{
	t_token_list	**tmp;

	tmp = head;
	while (*tmp && *(*tmp)->word && *(*tmp)->word == ' ' && (*tmp)->size--)
		(*tmp)->word++;
	while (*tmp && (*tmp)->next)
	{
		if ((*tmp)->next->type >= N_PIPE && (*tmp)->next->type <= N_HEREDOC)
		{
			while ((*tmp)->size && (*tmp)->word[(*tmp)->size - 1] == ' ')
				(*tmp)->size--;
			tmp = &(*tmp)->next->next;
			while (tmp && *(*tmp)->word && *(*tmp)->word == ' '
				&& (*tmp)->size--)
				(*tmp)->word++;
		}
		else
			tmp = &(*tmp)->next;
	}
	while (*tmp && (*tmp)->size && (*tmp)->word[(*tmp)->size - 1] == ' ')
		(*tmp)->size--;
}

int	lex_space(t_token_list **head)
{
	t_token_list	*token;
	t_token_list	**tmp;

	tmp = head;
	while (*tmp)
	{
		if ((*tmp)->type == T_ALL && ft_memchr((*tmp)->word, ' ', (*tmp)->size))
		{
			token = malloc(sizeof(t_token_list));
			if (!token)
				return (1);
			token->word = ft_memchr((*tmp)->word, ' ', (*tmp)->size) + 1;
			token->size = (*tmp)->size;
			(*tmp)->size = token->word - (*tmp)->word;
			token->size -= (*tmp)->size;
			token->type = T_ALL;
			token->next = (*tmp)->next;
			(*tmp)->next = token;
		}
		tmp = &(*tmp)->next;
	}
	return (0);
}

void	lexer(t_shell *shell)
{
	if (lex_quote(&shell->tokens, shell->input))
		frexit("Error in lex_quote", shell);
	lex_clean(&shell->tokens);
	if (mak_expnd(&shell->tokens))
		frexit("Error in mak_expnd", shell);
	lex_clean(&shell->tokens);
	lex_expnd(shell->tokens, shell->env, shell->value);
	lex_clean(&shell->tokens);
	if (lex_split(&shell->tokens))
		frexit("Error in lex_split", shell);
	lex_clean(&shell->tokens);
	lex_trims(&shell->tokens);
	lex_clean(&shell->tokens);
	if (lex_space(&shell->tokens))
		frexit("Error in lex_space", shell);
	lex_clean(&shell->tokens);
}
