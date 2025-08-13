/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/13 17:01:07 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freenv(t_minishell	*shell)
{
	free_env(&shell->env);
	free(shell);
}

int	main(int argc, char **argv, char *env[])
{
	t_minishell	*shell;

	if (argc != 1 || !argv)
		return (1);
	shell = malloc(sizeof(t_minishell));
	if (!shell)
		return (1);
	shell->value = "0";
	shell->env = copy_env(env, 0);
	if (parser(shell, "$TEST"))
		freenv(shell);
	/*if (parser(shell, "\"echo\" \'hi\' $USER \" are you $? !\""))
		freenv(shell);
	else if (parser(shell, "export TEST=eof"))
		freenv(shell);
	else if (parser(shell, "export LWC='-l'"))
		freenv(shell);
	else if (parser(shell, "rm out' '0"))
		freenv(shell);
	else if (parser(shell, " cat<<	$TEST |>>out' '\"$?\"	 wc $LWC <out' '0"))
		freenv(shell);
	else if (parser(shell, "cat out' '0"))
		freenv(shell);
	*/else
	{
		freenv(shell);
		return (0);
	}
	return (1);
}
/*
My big test :
mS>	export TEST=eof
mS>	export LWC='-l'
mS>	rm out' '0
mS>	 cat<<	$TEST |>>out' '"$?"	 wc $LWC <out' '0
($TEST)>	hello
($TEST)>	$TEST
mS>	cat out' '0
0
mS>	
*/