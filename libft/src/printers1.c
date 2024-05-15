/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:36:27 by jdemers           #+#    #+#             */
/*   Updated: 2024/02/09 14:11:49 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	print_string(char *str, int fd)
{
	if (!str)
		return (print_string("(null)", fd));
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	print_int(int n, int fd)
{
	int	i;

	ft_putnbr_fd(n, fd);
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	print_unsigned_int(unsigned int n, int fd)
{
	int	i;

	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((char)(n % 10 + '0'), fd);
	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
