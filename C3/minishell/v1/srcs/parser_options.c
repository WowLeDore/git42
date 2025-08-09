/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:36:26 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/07 13:14:36 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_options_len(t_token_list *tokens, char *str)
{
	size_t			count;
	t_token_list	*tmp;
	char			*ptr1;
	char			*ptr2;

	count = 0;
	tmp = tokens;
	ptr1 = str;
	ptr2 = str;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type > T_PIPE)
			ptr1++;
		if (tmp->type > T_PIPE)
			tmp = tmp->next;
		else if (ptr1 >= ptr2)
			count++;
		if (tmp && ptr1 >= ptr2)
			ptr2 += ft_strlen(ptr2) + 1;
		if (tmp)
			ptr1 += (tmp->type < T_PIPE) * tmp->size + (tmp->type >= T_PIPE);
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

char	**get_options(t_token_list *tokens, char *str)
{
	size_t			count;
	t_token_list	*tmp;
	char			*ptr;
	char			**options;

	count = 0;
	tmp = tokens;
	ptr = str;
	options = malloc(sizeof(char *) * (get_options_len(tokens, str) + 1));
	while (options && tmp && tmp->type != T_PIPE)
	{
		if (tmp->type > T_PIPE && (str++ || 1))
			tmp = tmp->next;
		else if (str >= ptr)
			options[count++] = str;
		if (tmp && str >= ptr)
			ptr += ft_strlen(ptr) + 1;
		if (tmp)
			str += (tmp->type < T_PIPE) * tmp->size + (tmp->type >= T_PIPE);
		if (tmp)
			tmp = tmp->next;
	}
	if (options)
		options[count] = NULL;
	return (options);
}

char	**get_redir(t_token_list *tokens, char *str, t_token redir)
{
	size_t			count;
	t_token_list	*tmp;
	char			**redirs;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type == redir && tmp->next && tmp->next->type < T_PIPE)
			count++;
		tmp = tmp->next;
	}
	redirs = malloc(sizeof(char *) * (count + 1));
	count = 0;
	tmp = tokens;
	while (redirs && tmp && tmp->type != T_PIPE)
	{
		if (tmp->type == redir && tmp->next && tmp->next->type < T_PIPE)
			redirs[count++] = str + 1;
		str += (tmp->type < T_PIPE) * tmp->size + (tmp->type >= T_PIPE);
		tmp = tmp->next;
	}
	if (redirs)
		redirs[count] = 0;
	return (redirs);
}

int	make_option(t_command_list *comms, size_t n, t_token_list *tok, char *str)
{
	comms[n].options = get_options(tok, str);
	if (!comms[n].options)
		return (1);
	comms[n].read = get_redir(tok, str, T_IN);
	if (!comms[n].read)
		return (1);
	comms[n].replace = get_redir(tok, str, T_OUT);
	if (!comms[n].replace)
		return (1);
	comms[n].append = get_redir(tok, str, T_APPEND);
	if (!comms[n].append)
		return (1);
	comms[n].heredoc = get_redir(tok, str, T_HEREDOC);
	if (!comms[n].heredoc)
		return (1);
	return (0);
}

int	make_options(t_command_list *comms, t_token_list *tok, char *str)
{
	size_t			i;
	t_token_list	*tmp;
	t_token			last;

	i = 0;
	tmp = tok;
	last = T_PIPE;
	if (make_option(comms, i, tmp, str))
		return (1);
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			if (make_option(comms, ++i, tmp->next, str + tmp->size))
				return (1);
		str += (tmp->type < T_PIPE) * tmp->size
			+ (tmp->type >= T_PIPE && last < T_PIPE);
		last = tmp->type;
		tmp = tmp->next;
	}
	return (0);
}
