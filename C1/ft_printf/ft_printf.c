#include <stdarg.h>
#include <stdio.h>

int	ft_printf(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		printf("%c\n", *(format++));
		printf("%c\n", va_arg(args, char));
	}
	va_end(args);
	return (0);
}
