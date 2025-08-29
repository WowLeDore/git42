/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:51:48 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/27 18:35:55 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search(t_comm *comm, char **env)
{
	size_t	len;

	if (!comm->word || !*comm->word)
		return (23);
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
	else
		return (search_file(comm, len, env));
	return (0);
}

int	execbi(t_comm *comm, char *argv[], char *envp[])
{
	(void) envp;
	if (comm->builtin == 1)
		return (b_echo(argv));
	return (1);
}
	/*if (comm->builtin == 2)
		return (b_cd(argv, envp));
	if (comm->builtin == 3)
		return (b_pwd());
	if (comm->builtin == 4)
		return (b_export(argv, envp));
	if (comm->builtin == 5)
		return (b_unset(argv, envp));
	if (comm->builtin == 6)
		return (b_env(envp));
	if (comm->builtin == 7)
		return (b_exit(argv));
	*/

int	rerror(char *err, int val)
{
	perror(err);
	return (val);
}

int	exec_simple(t_minishell *shell, t_comm *comm)
{
	int		code;
	pid_t	pid;
	int		status;

	code = search(comm, shell->env);
	if (!code)
		return (execbi(comm, comm->options, shell->env));
	if (code == 127 || code == 23)
		return (code);
	pid = fork();
	if (pid < 0)
		return (rerror("fork", 1));
	if (!pid)
		execve(comm->word, comm->options, shell->env);
	if (!pid)
		perror(comm->word);
	if (pid && code == 1)
		free(comm->word);
	if (pid && waitpid(pid, &status, 0) == -1)
		return (rerror("waitpid", 1));
	if (pid && WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (pid && WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
