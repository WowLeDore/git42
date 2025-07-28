/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:34:56 by mguillot          #+#    #+#             */
/*   Updated: 2025/07/28 17:46:46 by mguillot         ###   ########.fr       */
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

int	lex_trims(t_token_list **head)
{
	t_token_list	**tmp;
	t_token_list	*token;

	tmp = head;
	while (*tmp)
	{
		if ((*tmp)->type == T_ALL && ft_memchr((*tmp)->word, ' ', (*tmp)->size))
		{
			while (*(*tmp)->word == ' ' && (*tmp)->size--)
				(*tmp)->word++;
			while ((*tmp)->size && (*tmp)->word[(*tmp)->size - 1] == ' ')
				(*tmp)->size--;
			if (!ft_memchr((*tmp)->word, ' ', (*tmp)->size))
				continue ;
			token = rem_space(*tmp);
			if (!token)
				return (1);
			(*tmp)->next = token;
		}
		else
			tmp = &(*tmp)->next;
	}
	return (0);
}

void	lex_clean(t_token_list **head)
{
	t_token_list	**tmp;
	t_token_list	*to_free;

	tmp = head;
	while (*tmp)
	{
		if ((*tmp)->size < 1)
		{
			to_free = *tmp;
			*tmp = (*tmp)->next;
			free(to_free);
		}
		else
			tmp = &(*tmp)->next;
	}
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
}
	//if (lex_trims(&shell->tokens))
	//	frexit("Error in lex_trims", shell);
	//lex_clean(&shell->tokens);
