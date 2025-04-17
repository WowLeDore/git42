/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:48:58 by mguillot          #+#    #+#             */
/*   Updated: 2025/04/17 15:31:58 by mguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message = {NULL, 0, 0};

void	put_nbr(int n)
{
	char	c;

	if (n > 9)
		put_nbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void	add_char(unsigned char c)
{
	char	*buffer;
	int		capacity;
	int		i;

	if (g_message.i + 1 > g_message.capacity - 1)
	{
		capacity = g_message.capacity + BUFFER_SIZE;
		buffer = malloc(capacity);
		if (!buffer)
			exit(1);
		i = -1;
		while (g_message.buffer && ++i < g_message.i)
			buffer[i] = g_message.buffer[i];
		free(g_message.buffer);
		g_message.buffer = buffer;
		g_message.capacity = capacity;
	}
	if (c)
		g_message.buffer[g_message.i++] = c;
	else if (g_message.buffer)
	{
		write(1, g_message.buffer, g_message.i);
		write(1, "\n", 1);
		g_message.i = 0;
	}
}

void	handle_sig(int sig)
{
	static unsigned char	c = 0;
	static int				bit = 0;

	if (sig == SIGUSR1)
		c |= 1 << bit;
	bit++;
	if (bit == 8)
	{
		add_char(c);
		c = 0;
		bit = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	sigset_t			mask;

	if (argc != 1 || !argv)
		write(2, "Error: Incorrect arguments\nUsage: ./server\n", 43);
	if (argc != 1 || !argv)
		return (1);
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	sa.sa_handler = handle_sig;
	sa.sa_mask = mask;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID: ", 5);
	put_nbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
}
