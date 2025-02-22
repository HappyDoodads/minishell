/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:45:12 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/12 14:59:34 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_numlen(int n)
{
	unsigned int	i;

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

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	num_len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num_len = ft_numlen(n);
	s = ft_calloc(num_len + 1, sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	else if (n == 0)
		s[0] = '0';
	num_len--;
	while (n > 0)
	{
		s[num_len--] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}

char	*ft_itoab(int n, char *buf, size_t size)
{
	unsigned int	i;

	ft_bzero(buf, size);
	i = ft_numlen(n);
	if (i-- >= size)
		return (NULL);
	if (n == -2147483648)
		return (ft_strlcpy(buf, "-2147483648", size), buf);
	if (n < 0)
	{
		buf[0] = '-';
		n *= -1;
	}
	else if (n == 0)
		buf[0] = '0';
	while (n > 0)
	{
		buf[i--] = n % 10 + '0';
		n /= 10;
	}
	return (buf);
}
