/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:52:06 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/27 15:47:56 by mguillot         ###   ########.fr       */
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
	if (ft_strchr(comm->word, '/'))
	{
		if (exec_file(comm->word))
			return (2);
		perror(comm->word);
		return (127);
	}
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
