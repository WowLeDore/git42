/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:09:11 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/06 16:38:00 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

int	cd(int argc, char **argv, char **envp)
{
	int		status;
	char	*str;

	if (argc != 2)
		write(2, "cd: incorrect number of arguments\n", 34);
	else
	{
		str = get_env();
		status = chdir(argv[1]);

		perror("cd");
	}
	return (0);
}
