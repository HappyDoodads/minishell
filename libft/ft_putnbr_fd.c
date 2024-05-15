/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:28:30 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/20 11:29:03 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	copie;

	copie = n;
	if (copie < 0)
	{
		ft_putchar_fd('-', fd);
		copie = -copie;
	}
	if (copie >= 10)
	{
		ft_putnbr_fd(copie / 10, fd);
	}
	ft_putchar_fd('0' + copie % 10, fd);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("\nFonction ft_putnbr imprime des int en char\n\n");
// 	ft_putnbr_fd(42424242, 1);
// 	write(1, "\n\n", 2);
// 	return (0);
// }
