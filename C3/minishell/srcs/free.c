/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:56:44 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/20 19:19:08 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tok(t_token *tok)
{
	int		fd;
	void	*to_free;

	while (tok)
	{
		free_tok(tok->subs);
		if (tok->type == HEREDOC && tok->heredoc)
		{
			fd = open(tok->heredoc, O_RDONLY);
			if (fd >= 0)
			{
				unlink(tok->heredoc);
				close(fd);
			}
			free(tok->heredoc);
		}
		to_free = (void *) tok;
		tok = tok->next;
		free((t_token *) to_free);
	}
}

void	free_comms(t_comm *comm)
{
	void	*to_free;

	while (comm)
	{
		if (comm->options)
			free(comm->options);
		if (comm->ins)
			free(comm->ins);
		if (comm->outs)
			free(comm->outs);
		if (comm->appends)
			free(comm->appends);
		to_free = (void *) comm;
		comm = comm->next;
		free((t_comm *) to_free);
	}
}

void	free_all(t_minishell *shell)
{
	t_pipe	*tmp_pipe;
	void	*to_free;

	if (!shell)
		return ;
	tmp_pipe = shell->pipes;
	while (tmp_pipe)
	{
		free_tok(tmp_pipe->toks);
		to_free = (void *) tmp_pipe;
		tmp_pipe = tmp_pipe->next;
		free((t_pipe *) to_free);
	}
	if (shell->input)
		free(shell->input);
	if (shell->big_str)
		free(shell->big_str);
	free_comms(shell->comms);
}

void	free_env(char ***env)
{
	size_t	i;

	i = 0;
	while (*env && (*env)[i])
		free((*env)[i++]);
	if (*env)
		free(*env);
	*env = NULL;
}

void	frexit(t_minishell *shell, char *err_msg, int value)
{
	if (err_msg && !shell)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
		exit(value);
	}
	if (!shell)
		return ;
	free_all(shell);
	if (!err_msg)
		return ;
	free_env(&shell->env);
	free(shell);
	rl_clear_history();
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	exit(value);
}
