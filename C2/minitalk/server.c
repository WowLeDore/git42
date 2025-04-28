#include "minitalk.h"

static void	put_nbr(int n)
{
	char	c;

	if (n > 9)
		put_nbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

static void	add_char(unsigned char c)
{
	static char	buffer[1024];
	static int	index = 0;

	if (c == '\0' || index == 1023)
	{
		write(1, buffer, index);
		index = 0;
		if (c == '\0')
			write(1, "\n", 1);
	}
	else
		buffer[index++] = c;
}

static void	handle_sig(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit = 0;

	(void)context;
	if (sig == SIGUSR2)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		add_char(c);
		c = 0;
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1); // Acknowledge signal
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "PID: ", 5);
	put_nbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = handle_sig;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}