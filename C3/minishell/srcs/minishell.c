/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:23 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/25 14:49:14 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *shell, char *env[])
{
	shell->value = "0";
	shell->env = NULL;
	shell->input = NULL;
	shell->pipes = NULL;
	shell->big_str = NULL;
	shell->comms = NULL;
	shell->heredoc = 0;
	shell->env = copy_env(env, 0);
	if (!shell->env)
		frexit(shell, "Error in copy_env", 3);
	shell->input = readline("mSh:~# ");
}

void	reset_shell(t_minishell *shell)
{
	add_history(shell->input);
	if (!parser(shell))
	{
		//print_minishell(shell);
		exec(shell);
	}
	frexit(shell, NULL, 0);
	shell->input = NULL;
	shell->pipes = NULL;
	shell->big_str = NULL;
	shell->comms = NULL;
	shell->heredoc = 0;
	shell->input = readline("mSh:~# ");
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*shell;

	if (argc != 1 || !argv)
		frexit(NULL, "Wrong usage", 1);
	shell = malloc(sizeof(t_minishell));
	if (!shell)
		frexit(NULL, "Error in main", 2);
	init_shell(shell, env);
	while (shell->input)
		reset_shell(shell);
	frexit(shell, NULL, 0);
	free_env(&shell->env);
	free(shell);
	rl_clear_history();
	write(1, "exit\n", 5);
	exit(0);
}
/*
My big test :
mS> export TEST=eof
mS> export LWC='-l'
mS> rm out' '0
mS>  cat<<	$TEST |>>out' '"$?"	 wc $LWC <out' '0
($TEST)> hello
($TEST)> $TEST
mS> cat out' '0
0
mS> 
*/