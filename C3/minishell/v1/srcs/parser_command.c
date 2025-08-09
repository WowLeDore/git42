/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:27:51 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/06 22:05:06 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_command(t_command_list *commands, size_t i)
{
		commands[i].command = NULL;
		commands[i].options = NULL;
		commands[i].read = NULL;
		commands[i].replace = NULL;
		commands[i].append = NULL;
		commands[i].heredoc = NULL;
}

size_t	command_count(t_token_list *tokens)
{
	size_t			i;
	t_token_list	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		i += tmp->type == T_PIPE;
		tmp = tmp->next;
	}
	return (i + 1);
}

void	assign_commands(t_command_list *commands, t_token_list *toks, char *str,
	size_t n)
{
	size_t			i;
	t_token_list	*tmp;
	t_token			last;

	i = 0;
	while (i < n)
		init_command(commands, i++);
	i = 0;
	tmp = toks;
	last = T_PIPE;
	while (i < n - 1)
	{
		if (!commands[i].command)
			commands[i].command = str;
		i += (tmp != NULL && tmp->type == T_PIPE) || tmp == NULL;
		if (tmp)
		{
			str += (tmp->type < T_PIPE) * tmp->size
				+ (tmp->type >= T_PIPE && last < T_PIPE);
			last = tmp->type;
			tmp = tmp->next;
		}
	}
}
