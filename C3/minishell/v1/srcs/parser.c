/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:00:04 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/06 22:04:27 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	tot_len(t_token_list *tokens)
{
	size_t			i;
	t_token_list	*tmp;
	t_token			last;

	i = 0;
	tmp = tokens;
	last = T_PIPE;
	while (tmp)
	{
		i += (tmp->type < T_PIPE) * tmp->size
			+ (tmp->type >= T_PIPE && last < T_PIPE);
		last = tmp->type;
		tmp = tmp->next;
	}
	return (i);
}

size_t	space_split(char *str, size_t n)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			str[i] = '\0';
			count = count + 1;
		}
		i++;
	}
	return (count);
}

size_t	type_copy(t_token type, size_t size, char *src, char *dst)
{
	size_t	count;

	count = 0;
	if (type == T_VAL && size == 1)
		dst[0] = ((unsigned char) *src % 10) + '0';
	else if (type == T_VAL && size == 2)
	{
		dst[0] = (((unsigned char) *src / 10) % 10) + '0';
		dst[1] = ((unsigned char) *src % 10) + '0';
	}
	else if (type == T_VAL && size == 3)
	{
		dst[0] = ((unsigned char) *src / 100) + '0';
		dst[1] = (((unsigned char) *src / 10) % 10) + '0';
		dst[2] = ((unsigned char) *src % 10) + '0';
	}
	else if (type < T_PIPE)
		ft_memcpy(dst, src, size);
	if (type == T_ALL)
		count += space_split(dst, size);
	return (count);
}

size_t	copy_str(t_token_list *tokens, char *str)
{
	size_t			i;
	size_t			count;
	t_token_list	*tmp;
	t_token			last;

	i = 0;
	count = 0;
	tmp = tokens;
	last = T_PIPE;
	while (tmp)
	{
		count += type_copy(tmp->type, tmp->size, tmp->word, str + i);
		if (tmp->type >= T_PIPE && last < T_PIPE)
			str[i + 0 * count++] = '\0';
		i += (tmp->type < T_PIPE) * tmp->size
			+ (tmp->type >= T_PIPE && last < T_PIPE);
		last = tmp->type;
		tmp = tmp->next;
	}
	str[i] = '\0';
	return (count + 1);
}

void	parse(t_shell *shell)
{
	if (!tot_len(shell->tokens))
		return ;
	shell->tot_str = malloc(sizeof(char) * (tot_len(shell->tokens) + 1));
	if (!shell->tot_str)
		frexit(shell, "Error in parse");
	shell->str_nbr = copy_str(shell->tokens, shell->tot_str);
	shell->commands = malloc(sizeof(t_command_list)
			* (command_count(shell->tokens) + 1));
	if (!shell->commands)
		frexit(shell, "Error in parse");
	assign_commands(shell->commands, shell->tokens, shell->tot_str,
		command_count(shell->tokens) + 1);
	if (make_options(shell->commands, shell->tokens, shell->tot_str))
		frexit(shell, "Error in make_options");
}
