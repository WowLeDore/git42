/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:34:56 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/02 19:35:46 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	delete(t_token_list *head, t_token last)
{
	int		space;

	if (head->type != T_ALL)
		return (0);
	space = head->size == 1 && (*head->word == ' ' || *head->word == '\t');
	if (!head->next || (head->next->type >= N_PIPE
			&& head->next->type <= N_HEREDOC)
		|| (last >= N_PIPE && last <= N_HEREDOC))
		return (space);
	if (head->next->type != T_ALL)
		return (0);
	return (space && head->next->size == 1 && (*head->next->word == ' '
			|| *head->next->word == '\t'));
}

void	lex_clean(t_token_list **head)
{
	t_token_list	**tmp;
	t_token_list	*to_free;
	t_token			last;

	tmp = head;
	last = N_PIPE;
	while (*tmp)
	{
		if ((*tmp)->size < 1 || delete(*tmp, last))
		{
			to_free = *tmp;
			*tmp = (*tmp)->next;
			free(to_free);
		}
		else
		{
			last = (*tmp)->type;
			tmp = &(*tmp)->next;
		}
	}
}

void	make_space(t_token_list *space, t_token_list *token, t_token_list **tmp)
{
	space->word = first_char((*tmp)->word, (*tmp)->size, ' ', '\t');
	token->size = (*tmp)->size - (space->word - (*tmp)->word) - 1;
	space->size = 1;
	space->type = T_ALL;
	space->next = token;
	(*tmp)->size = space->word - (*tmp)->word;
	token->word = space->word + 1;
	token->type = T_ALL;
	token->next = (*tmp)->next;
	(*tmp)->next = space;
	space->word = " ";
}

int	lex_space(t_token_list **head)
{
	t_token_list	*space;
	t_token_list	*token;
	t_token_list	**tmp;

	tmp = head;
	while (*tmp)
	{
		if ((*tmp)->type == T_ALL
			&& first_char((*tmp)->word, (*tmp)->size, ' ', '\t'))
		{
			space = malloc(sizeof(t_token_list));
			if (!space)
				return (1);
			token = malloc(sizeof(t_token_list));
			if (!token)
				free(space);
			if (!token)
				return (1);
			make_space(space, token, tmp);
			tmp = &(*tmp)->next;
		}
		tmp = &(*tmp)->next;
	}
	return (0);
}

void	lexer(t_shell *shell)
{
	if (lex_quote(&shell->tokens, shell->input))
		frexit(shell, "Error in lex_quote");
	lex_clean(&shell->tokens);
	if (lex_split(&shell->tokens))
		frexit(shell, "Error in lex_split");
	lex_clean(&shell->tokens);
	if (lex_space(&shell->tokens))
		frexit(shell, "Error in lex_space");
	lex_clean(&shell->tokens);
	if (mak_expnd(&shell->tokens))
		frexit(shell, "Error in mak_expnd");
	lex_clean(&shell->tokens);
	lex_expnd(shell->tokens, shell->env, shell->value);
	lex_clean(&shell->tokens);
}
