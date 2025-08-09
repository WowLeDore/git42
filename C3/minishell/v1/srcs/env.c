/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:08:25 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/05 19:31:13 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(char **env, size_t add)
{
	char	**new_env;
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1 + add));
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

char	*get_env(char **env, char *key, size_t key_len)
{
	while (env && *env)
	{
		if (!ft_strncmp(key, *env, key_len) && (*env)[key_len] == '=')
			return ((*env) + key_len + 1);
		env++;
	}
	return (NULL);
}

int	change_env(char **env, char *key, size_t key_len, char *value)
{
	size_t	i;
	size_t	val_len;

	if (!env)
		return (0);
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], key_len) && env[i][key_len] == '=')
			break ;
		i++;
	}
	free(env[i]);
	val_len = ft_strlen(value);
	env[i] = malloc(sizeof(char) * (key_len + val_len + 2));
	if (!env[i])
		return (1);
	ft_memcpy(env[i], key, key_len);
	env[i][key_len] = '=';
	ft_memcpy(env[i] + key_len + 1, value, val_len);
	env[i][key_len + val_len + 1] = '\0';
	return (0);
}

int	add_env(char ***env, char *key, size_t key_len, char *value)
{
	size_t	i;
	size_t	val_len;
	char	**new_env;

	new_env = copy_env(*env, 1);
	if (!new_env)
		return (1);
	i = 0;
	while (new_env[i])
		i++;
	val_len = ft_strlen(value);
	new_env[i] = malloc(sizeof(char) * (key_len + val_len + 2));
	if (!new_env[i])
	{
		free_env(&new_env);
		return (1);
	}
	ft_memcpy(new_env[i], key, key_len);
	new_env[i][key_len] = '=';
	ft_memcpy(new_env[i] + key_len + 1, value, val_len);
	new_env[i][key_len + val_len + 1] = '\0';
	new_env[i + 1] = NULL;
	free_env(env);
	*env = new_env;
	return (0);
}

int	remove_env(char	***env, char *key, size_t key_len)
{
	size_t	i;
	char	**new_env;

	if (!(*env))
		return (0);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp(key, (*env)[i], key_len) && (*env)[i][key_len] == '=')
			break ;
		i++;
	}
	free((*env)[i]);
	while ((*env)[++i])
		(*env)[i - 1] = (*env)[i];
	(*env)[i - 1] = (*env)[i];
	new_env = copy_env(*env, 0);
	if (!new_env)
		return (1);
	free_env(env);
	*env = new_env;
	return (0);
}
