/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:00:59 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/18 16:06:12 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename(size_t count)
{
	char	file[45];
	int		i;

	i = 44;
	file[i] = 0;
	if (!count)
		file[--i] = '0';
	while (count)
	{
		file[--i] = '0' + (count % 10);
		count /= 10;
	}
	count = 23;
	while (count)
		file[--i] = "_codereh_llehsinim/pmt/"[23 - count--];
	return (ft_strdup(file + i));
}

int	heredoc_loop(char *prompt, char *delimiter, size_t size, int fd)
{
	size_t	len;
	char	*line;

	len = 0;
	line = readline(prompt);
	if (line)
		len = ft_strlen(line);
	if (len == size && ft_strncmp(line, delimiter, len) == 0)
	{
		free(line);
		return (0);
	}
	write(fd, line, len);
	write(fd, "\n", 1);
	free(line);
	return (1);
}

int	heredoc_init(int fd, char *delimiter)
{
	char	*tmp;
	char	*prompt;
	size_t	len;

	tmp = ft_strjoin("(", delimiter);
	if (!tmp)
		return (1);
	prompt = ft_strjoin(tmp, ")> ");
	free(tmp);
	if (!prompt)
		return (1);
	len = ft_strlen(delimiter);
	while (heredoc_loop(prompt, delimiter, len, fd))
		;
	free(prompt);
	return (0);
}

int	handle_heredoc(t_token *token, char *delimiter, size_t count)
{
	int		fd;

	token->heredoc = filename(count);
	if (!token->heredoc)
		return (1);
	fd = open(token->heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (1);
	if (heredoc_init(fd, delimiter))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	heredoc(t_minishell *shell)
{
	t_pipe			*pipe;
	t_token			*token;
	char			*ptr;

	pipe = shell->pipes;
	ptr = shell->big_str;
	while (pipe)
	{
		token = pipe->toks;
		while (token)
		{
			if (token->type == HEREDOC)
			{
				if (handle_heredoc(token, ptr, shell->heredoc++))
					return (1);
			}
			ptr += ft_strlen(ptr) + 1;
			token = token->next;
		}
		pipe = pipe->next;
	}
	return (0);
}
