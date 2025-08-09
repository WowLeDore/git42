/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/09 18:53:20 by mguillot         ###   ########.fr       */
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
	if (parser("export TEST=eof", shell))
		free(shell);
	else if (parser("export LWC='-l'", shell))
		free(shell);
	else if (parser("rm out' '0", shell))
		free(shell);
	else if (parser(" cat<<	$TEST |>>out' '\"$?\"	 wc $LWC <out' '0", shell))
		free(shell);
	else if (parser("cat out' '0", shell))
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