/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:01:56 by pbona             #+#    #+#             */
/*   Updated: 2025/06/29 18:06:15 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	err(char *str, int errno)
{
	printf("%s\n", str);
	return (errno);
}

int	big_free(int errno, char *free1, char **free2)
{
	int	i;

	if (free1)
		free(free1);
	if (free2)
	{
		i = 0;
		while (free2[i])
			free(free2[i++]);
		free(free2[i]);
		free(free2);
	}
	rl_clear_history();
	return (errno);
}

int	main(int ac, char *av[])
{
	char	*input;
	char	**args;
	pid_t	childpid;

	if (ac != 1 || !av)
		return (1);
	while (1)
	{
		input = readline("MEGASHELL:~# ");
		if (!input)
			return (big_free(err("exit", 0), NULL, NULL));
		if (*input)
			add_history(input);
		args = ft_split(input, ' ');
		if (!args)
			return (big_free(err("Args malloc fail", 1), input, NULL));
		childpid = fork();
		if (childpid == 0)
			if (execve(*args, args, environ))
				return (big_free(err("Command not found", 2), input, args));
		else if (childpid > 0)
			waitpid(childpid, 0, 0);
		big_free(0, input, args);
	}
	return (0);
}
