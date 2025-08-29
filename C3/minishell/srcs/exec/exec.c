/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:10:17 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/27 18:34:38 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_stdin(t_comm *comm, t_type type, size_t *i_in)
{
	char	*file;
	int		fd;

	if (type == IN)
		file = comm->ins[(*i_in)++];
	else
		file = comm->heredoc;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		frexit(NULL, "file error", EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_stdout(t_comm *comm, t_type type, size_t *i_ou, size_t *i_ap)
{
	char	*file;
	int		flag;
	int		fd;

	if (type == OUT)
		file = comm->outs[(*i_ou)++];
	else
		file = comm->appends[(*i_ap)++];
	if (type == OUT)
		flag = O_TRUNC;
	else
		flag = O_APPEND;
	fd = open(file, O_WRONLY | O_CREAT | flag, 0644);
	if (fd == -1)
	{
		perror(file);
		frexit(NULL, "file error", EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirs(t_comm *comm, t_pipe *pipe)
{
	t_token	*tok;
	size_t	i_in;
	size_t	i_ap;
	size_t	i_ou;

	tok = pipe->toks;
	i_in = 0;
	i_ap = 0;
	i_ou = 0;
	while (tok)
	{
		if (tok->type == HEREDOC || tok->type == IN)
			handle_stdin(comm, tok->type, &i_in);
		else if (tok->type == APPEND || tok->type == OUT)
			handle_stdout(comm, tok->type, &i_ou, &i_ap);
		tok = tok->next;
	}
}

int	exec(t_minishell *shell)
{
	t_comm	*comm;
	t_pipe	*pipe;
	int		backups[2];

	comm = shell->comms;
	pipe = shell->pipes;
	while (comm && pipe)
	{
		backups[0] = dup(STDIN_FILENO);
		backups[1] = dup(STDOUT_FILENO);
		handle_redirs(comm, pipe);
		exec_simple(shell, comm);
		dup2(backups[0], STDIN_FILENO);
		dup2(backups[1], STDOUT_FILENO);
		close(backups[0]);
		close(backups[1]);
		comm = comm->next;
		pipe = pipe->next;
	}
	return (0);
}

int	exec_pipe(t_minishell *shell)
{
	t_comm	*tmp_comm;
	t_pipe	*tmp_pipe;
	int		prev_fd;
	int		fd[2];
	pid_t	pid;
	int		status;

	tmp_comm = shell->comms;
	tmp_pipe = shell->pipes;
	prev_fd = -1;
	while (tmp_comm && tmp_pipe)
	{
		if (tmp_pipe->next && pipe(fd) == -1)
			return (rerror("pipe", 1));
		pid = fork();
		if (pid < 0)
			return (rerror("fork", 1));
		if (!pid)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (tmp_pipe->next)
			{
				close(fd[0]);
				dup2(fd[1], STDIN_FILENO);
				close(fd[1]);
			}
			handle_redirs(tmp_comm, tmp_pipe);
			frexit(shell, NULL, exec_simple(shell, tmp_comm));
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (tmp_pipe->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		else
			prev_fd = -1;
		tmp_comm = tmp_comm->next;
		tmp_pipe = tmp_pipe->next;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
