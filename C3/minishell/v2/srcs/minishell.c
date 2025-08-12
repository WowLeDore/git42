/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/12 18:11:41 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_minishell	*shell;

	if (argc != 1 || !argv)
		return (1);
	shell = malloc(sizeof(t_minishell));
	if (!shell)
		return (1);
	if (parser(shell, "\"echo\" \'hi\' $USER \" are you $?\""))
		free(shell);
	else if (parser(shell, "export TEST=eof"))
		free(shell);
	else if (parser(shell, "export LWC='-l'"))
		free(shell);
	else if (parser(shell, "rm out' '0"))
		free(shell);
	else if (parser(shell, " cat<<	$TEST |>>out' '\"$?\"	 wc $LWC <out' '0"))
		free(shell);
	else if (parser(shell, "cat out' '0"))
		free(shell);
	else
	{
		free(shell);
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