/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:10:17 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/20 19:31:31 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_builtin(t_comm *comm)
{
	size_t	len;

	len = ft_strlen(comm->word);
	if (len == 4 && !ft_strncmp(comm->word, "echo", len))
		comm->builtin = 1;
	else if (len == 2 && !ft_strncmp(comm->word, "cd", len))
		comm->builtin = 2;
	else if (len == 3 && !ft_strncmp(comm->word, "pwd", len))
		comm->builtin = 3;
	else if (len == 6 && !ft_strncmp(comm->word, "export", len))
		comm->builtin = 4;
	else if (len == 5 && !ft_strncmp(comm->word, "unset", len))
		comm->builtin = 5;
	else if (len == 3 && !ft_strncmp(comm->word, "env", len))
		comm->builtin = 6;
	else if (len == 4 && !ft_strncmp(comm->word, "exit", len))
		comm->builtin = 7;
}

int	exec_simple(t_comm *comm, char **env)
{
	pid_t	pid;

	search_builtin(comm);
	//if (!comm->builtin)
	//	search_path(comm);
	//if (comm->builtin)
	//	return (execbi(comm->word, comm->options, env));
	pid = fork();
	if (!pid && execve(comm->word, comm->options, env) == -1)
	{
		perror(comm->word);
		exit(EXIT_FAILURE);
	}
	else if (pid)
		waitpid(pid, NULL, 0);
	return (0);
}

void	handle_stdin(t_comm *comm, t_type type, size_t *i_in)
{
	char	*file;
	int		fd;

	if (type == IN)
		file = comm->ins[*(i_in++)];
	else
		file = comm->heredoc;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(comm->ins[*i_in]);
		exit(EXIT_FAILURE);
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
		file = comm->outs[*(i_ou++)];
	else
		file = comm->appends[*(i_ap++)];
	if (type == OUT)
		flag = O_TRUNC;
	else
		flag = O_APPEND;
	fd = open(file, O_WRONLY | O_CREAT | flag, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	exec_comm(t_comm *comm, t_pipe *pipe, char **env)
{
	t_token	*tok;
	size_t	i_in;
	size_t	i_ap;
	size_t	i_ou;

	//if (comm->next)
	//	handle_pipe(comm);
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
	return (exec_simple(comm, env));
}

int	freexec(char **env, char *value, int ret)
{
	if (env)
		free_env(&env);
	if (value)
		free(value);
	return (ret);
}

int	exec(t_minishell *shell)
{
	t_comm	*comm;
	t_pipe	*pipe;
	char	**env;
	char	*value;

	comm = shell->comms;
	pipe = shell->pipes;
	env = copy_env(shell->env, 0);
	value = ft_strdup(shell->value);
	if (!env || !value)
		return (freexec(env, value, 1));
	while (comm && pipe)
	{
		if (exec_comm(comm, pipe, env))
			return (freexec(env, value, 1));
		comm = comm->next;
		pipe = pipe->next;
	}
	return (freexec(env, value, 0));
}
