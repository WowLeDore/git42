/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 08:19:44 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/14 08:32:54 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_space(t_token **sub, size_t i)
{
	t_token	*tk;

	tk = malloc(sizeof(t_token));
	if (!tk)
		return (1);
	tk->next = (*sub)->next;
	(*sub)->next = tk;
	tk->type = XPNDED;
	tk->size = (*sub)->size - i - 1;
	tk->word = (*sub)->word + i + 1;
	tk->subs = NULL;
	(*sub)->size = i;
	return (0);
}

int	split(t_token *subs)
{
	t_token	*tmp_sub;
	int		quote;
	size_t	i;

	tmp_sub = subs;
	quote = 0;
	while (tmp_sub)
	{
		if (!quote && tmp_sub->type == XPNDED)
		{
			i = 0;
			while (i < tmp_sub->size)
			{
				if ((tmp_sub->word[i] == ' ' || tmp_sub->word[i] == '\t'
						|| tmp_sub->word[i] == '\n')
					&& handle_space(&tmp_sub, i))
					return (1);
				i++;
			}
		}
		if (tmp_sub->type == SQUOTE || tmp_sub->type == DQUOTE)
			quote = 1 - quote;
		tmp_sub = tmp_sub->next;
	}
	return (0);
}

int	word_split(t_minishell *shell)
{
	t_pipe	*tmp_pipe;
	t_token	*tmp_tok;

	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		tmp_tok = tmp_pipe->toks;
		while (tmp_tok)
		{
			if (tmp_tok->type <= HEREDOC && split(tmp_tok->subs))
				return (1);
			tmp_tok = tmp_tok->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
	return (0);
}
