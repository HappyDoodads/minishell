/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:34:47 by jdemers           #+#    #+#             */
/*   Updated: 2024/02/09 14:19:04 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexlen(unsigned long n)
{
	int	hex_len;

	if (n < 16)
		return (1);
	hex_len = 0;
	while (n > 0)
	{
		n /= 16;
		hex_len++;
	}
	return (hex_len);
}

static char	ft_hexchar(unsigned long n, const char *base)
{
	return (base[n]);
}

int	print_hex(unsigned long n, char type, int fd)
{
	int		hex_len;
	char	*hex;
	int		i;

	hex_len = ft_hexlen(n);
	hex = malloc(hex_len + 1);
	if (!hex)
		return (-1);
	hex[hex_len] = '\0';
	i = hex_len - 1;
	while (i >= 0)
	{
		if (type == 'x')
			hex[i] = ft_hexchar(n % 16, "0123456789abcdef");
		else
			hex[i] = ft_hexchar(n % 16, "0123456789ABCDEF");
		n /= 16;
		i--;
	}
	ft_putstr_fd(hex, fd);
	free(hex);
	return (hex_len);
}

int	print_ptr(void *ptr, int fd)
{
	ft_putstr_fd("0x", fd);
	return (2 + print_hex((unsigned long)ptr, 'x', fd));
}
