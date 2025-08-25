/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:10:17 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/25 17:59:36 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_file(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	if (!S_ISREG(st.st_mode))
		return (0);
	return (access(path, X_OK) == 0);
}

char	*get_file(char *dir, char *str, size_t len)
{
	size_t	size;
	char	*file;

	size = ft_strlen(dir) + 1 + len + 1;
	file = malloc(sizeof(char) * size);
	if (!file)
		return (NULL);
	ft_strlcpy(file, dir, size);
	ft_strlcat(file, "/", size);
	ft_strlcat(file, str, size);
	if (exec_file(file))
		return (file);
	free(file);
	return (NULL);
}

void	free_split(char ***split)
{
	size_t	len;

	len = 0;
	while (*split && (*split)[len])
	{
		if ((*split)[len])
			free((*split)[len]);
		len++;
	}
	if (*split)
		free(*split);
	*split = NULL;
}

char	*find_path(char *str, size_t len, char **env)
{
	char	*path;
	char	**dirs;
	char	*file;
	size_t	i;

	path = get_env(env, "PATH", 4);
	if (!path || !*path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs && dirs[i])
	{
		file = get_file(dirs[i++], str, len);
		if (file)
			break ;
	}
	free_split(&dirs);
	return (file);
}

int	search_file(t_comm *comm, size_t len, char **env)
{
	char	*file;

	if (!comm->word || !*comm->word)
		return (127);
	if (ft_strchr(comm->word, '/') && !exec_file(comm->word))
		return (0);
	file = find_path(comm->word, len, env);
	if (file)
		comm->word = file;
	if (file)
		return (1);
	write(2, "mSh: ", 5);
	write(2, comm->word, len);
	write(2, " : command not found\n", 21);
	return (127);
}

int	search(t_comm *comm, size_t len, char **env)
{
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
	return (1);
}

int	rerror(char *err, int val)
{
	perror(err);
	return (val);
}

int	exec_simple(t_comm *comm, char **env)
{
	int		code;
	pid_t	pid;
	int		status;

	code = search(comm, ft_strlen(comm->word), env);
	if (!code)
		return (execbi(comm, comm->options, env));
	pid = fork();
	if (pid < 0)
		return (rerror("fork", 1));
	if (!pid)
		execve(comm->word, comm->options, env);
	if (!pid)
		perror(comm->word);
	if (code == 1)
		free(comm->word);
	if (waitpid(pid, &status, 0) == -1)
		return (rerror("waitpid", 1));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	handle_stdin(t_comm *comm, t_type type, size_t *i_in)
{
	char	*file;
	int		fd;

	if (type == IN)
		file = comm->ins[*i_in];
	if (type == IN)
		*i_in = *i_in + 1;
	else
		file = comm->heredoc;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
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
	{
		file = comm->outs[*i_ou];
		flag = O_TRUNC;
		*i_ou = *i_ou + 1;
	}
	else
	{
		file = comm->appends[*i_ap];
		flag = O_APPEND;
		*i_ap = *i_ap + 1;
	}
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
	int		backups[2];

	comm = shell->comms;
	pipe = shell->pipes;
	while (comm && pipe)
	{
		backups[0] = dup(STDIN_FILENO);
		backups[1] = dup(STDOUT_FILENO);
		exec_comm(comm, pipe, shell->env);
		dup2(backups[0], STDIN_FILENO);
		dup2(backups[1], STDOUT_FILENO);
		close(backups[0]);
		close(backups[1]);
		comm = comm->next;
		pipe = pipe->next;
	}
	return (0);
}
