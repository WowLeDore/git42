int	str_nbr(char *s)
{
	int	n;

	n = 0;
	while (*s >= '0' && *s <= '9')
		n = 10 * n + (*(s++) - '0');
	return (n);
}

int	verif(char *s, int len)
{
	if (s && *s >= '0' && *s <= '9')
		return (len < 8 && (!*(s + 1) || verif(s + 1, len + 1)));
	return (0);
}
