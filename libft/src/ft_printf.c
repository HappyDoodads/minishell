/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:25:56 by jdemers           #+#    #+#             */
/*   Updated: 2024/02/09 14:53:30 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	print_arg(int fd, char type, va_list args)
{
	if (type == 'c')
		return (print_char(va_arg(args, int), fd));
	if (type == 's')
		return (print_string(va_arg(args, char *), fd));
	if (type == 'p')
		return (print_ptr(va_arg(args, void *), fd));
	if (type == 'd' || type == 'i')
		return (print_int(va_arg(args, int), fd));
	if (type == 'x' || type == 'X')
		return (print_hex(va_arg(args, unsigned int), type, fd));
	if (type == 'u')
		return (print_unsigned_int(va_arg(args, unsigned int), fd));
	if (type == '%')
		return (print_char('%', fd));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned int	printed;
	unsigned int	tmp;

	va_start(args, format);
	printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			tmp = print_arg(1, *(++format), args);
			if (tmp < 0)
			{
				va_end(args);
				return (tmp);
			}
			printed += tmp;
		}
		else
			printed += print_char(*format, 1);
		format++;
	}
	va_end(args);
	return (printed);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list			args;
	unsigned int	printed;
	unsigned int	tmp;

	va_start(args, format);
	printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			tmp = print_arg(fd, *(++format), args);
			if (tmp < 0)
			{
				va_end(args);
				return (tmp);
			}
			printed += tmp;
		}
		else
			printed += print_char(*format, fd);
		format++;
	}
	va_end(args);
	return (printed);
}

/*
int	main(void)
{
	int	a;

	a = ft_printf("Hello %d, this is a %s\n", 42, "test");
	ft_printf("I printed %i characters\n", a);
	return (0);
}*/
