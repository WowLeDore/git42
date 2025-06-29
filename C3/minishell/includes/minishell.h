/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:27:49 by pbona             #+#    #+#             */
/*   Updated: 2025/06/29 21:41:31 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf/ft_printf.h"
# include "ft_get_next_line/get_next_line.h"

# include "tokens.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

/*structures*/
typedef struct s_line
{
	t_token_list	*tokens;
}	t_line;

typedef struct s_shell
{
	t_line	line;
}	t_shell;

/*fonctions*/
t_token_list	*lex(char *str);

#endif
