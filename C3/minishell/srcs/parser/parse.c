/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:00:51 by mguillot          #+#    #+#             */
/*   Updated: 2025/08/27 15:25:36 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_minishell *shell)
{
	shell->pipes = malloc(sizeof(t_pipe));
	if (!shell->pipes)
		frexit(shell, "Error in parser", 4);
	if (init_pipe(shell->pipes, shell->input))
		frexit(shell, "Error in init_pipe", 5);
	if (spliter(shell->pipes))
		frexit(shell, "Error in spliter", 6);
	group_operators(shell);
	remove_meta(shell);
	if (checker(shell) && (empty(shell)
			|| (write(2, "Syntax error\n", 13) * 0 + 1)))
		return (1);
	group_redirections(shell);
	if (sub_quote(shell))
		frexit(shell, "Error in sub_quote", 7);
	if (expand_vars(shell))
		frexit(shell, "Error in expand_vars", 8);
	if (word_split(shell))
		frexit(shell, "Error in word_split", 9);
	clean(shell);
	if (make_commands(shell))
		frexit(shell, "Error in make_commands", 10);
	return (0);
}
