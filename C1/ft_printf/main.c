int	ft_printf(const char *str, ...);

int	main(int argc, char **argv)
{
	if (argc != 1 || !argv)
		return (1);
	ft_printf("Coucou",'g',1);
	return (0);
}
