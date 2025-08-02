/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:08:25 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/02 15:59:23 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(char **env)
{
	char	**new_env;
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (new_env && j < i)
	{
		new_env[j] = ft_strdup(env[j]);
		if (!new_env[j])
		{
			i = 0;
			while (i < j)
				free(new_env[i++]);
			free(new_env);
			return (NULL);
		}
		j++;
	}
	if (new_env)
		new_env[i] = NULL;
	return (new_env);
}
