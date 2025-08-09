/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:29:49 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/04 12:43:29 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token_list *head)
{
	t_token_list	*tmp;

	while (head)
	{
		tmp = head->next;
		head->next = NULL;
		free(head);
		head = NULL;
		head = tmp;
	}
}

void	free_commands(t_command_list *commands)
{
	size_t	i;

	if (!commands)
		return ;
	i = 0;
	while (commands[i].command)
	{
		if (commands[i].options)
			free(commands[i].options);
		if (commands[i].read)
			free(commands[i].read);
		if (commands[i].replace)
			free(commands[i].replace);
		if (commands[i].append)
			free(commands[i].append);
		if (commands[i].heredoc)
			free(commands[i].heredoc);
		i++;
	}
	free(commands);
}

void	free_env(char ***env)
{
	size_t	i;

	i = 0;
	while (*env && (*env)[i])
		free((*env)[i++]);
	if (*env)
		free(*env);
}

void	frexit(t_shell *shell, char *err_msg)
{
	if (!shell && err_msg)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
		exit(1);
	}
	else if (!shell)
		return ;
	if (shell->input)
		free(shell->input);
	free_tokens(shell->tokens);
	if (shell->tot_str)
		free(shell->tot_str);
	free_commands(shell->commands);
	if (!err_msg)
		return ;
	free_env(&shell->env);
	free(shell);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	exit(1);
}
