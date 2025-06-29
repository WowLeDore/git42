/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:56 by pbona             #+#    #+#             */
/*   Updated: 2025/06/29 02:29:17 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	nb_args(char *str)
{
	int	args;

	args = 1;
	while (*str)
	{
		while (*str && *str != ' ')
			str++;
		while (*str && *str == ' ')
			str++;
		if (*str)
			args++;
	}
	return (args);
}

int	err(char *str, int errno)
{
	printf("%s\n", str);
	return (errno);
}

int	main(int ac, char *av[])
{
	int		status;
	char	*input;
	char	**args;
	pid_t	childpid;

	if (ac != 1 || !av)
		return (1);
	while (1)
	{
		input = readline("MEGASHELL:~# ");
		if (!input)
			return (err("Empty Input", 1));
		if (*input)
			add_history(input);
		// single command
		args = malloc(sizeof(char *) * nb_args(input));
		if (!args)
			return (err("Args malloc fail", 2));
		args = ft_split(input, ' ');
		if (!args)
			return (err("args", 3));
		childpid = fork();
		if (childpid == 0)
		{
			execve(*args, args, environ);
			return (err("execve", 4));
		}
		else if (childpid > 0)
			waitpid(childpid, &status, 0);
		else
			return (err("fork", 5));
		free(args);
		free(input);
	}
	return (0);
}
