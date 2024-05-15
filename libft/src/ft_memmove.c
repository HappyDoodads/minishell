/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:45:25 by jdemers           #+#    #+#             */
/*   Updated: 2023/10/17 10:23:42 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	move(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	revmove(char *dst, char *src, size_t len)
{
	size_t	i;

	i = len;
	while (i > 0)
	{
		i--;
		dst[i] = src[i];
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst < src)
		move((char *)dst, (char *)src, len);
	else if (dst > src)
		revmove((char *)dst, (char *)src, len);
	return (dst);
}
/*
#include <stdio.h>
int	main(void)
{
	char s1[11] = "0123456789";
	char s2[11] = "abcdefghij";

	ft_memmove(s1, s1 + 2, 4);
	ft_memmove(s2 + 2, s2, 4);
	printf("s1 = %s \t s2 = %s\n", (char*)s1, (char*)s2);
	return (0);
}*/
