/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:25:55 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/16 10:22:03 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countsize(long int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		i += 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb2;
	char	*str;
	size_t	size;

	nb2 = n;
	size = ft_countsize(nb2);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	if (nb2 < 0)
	{
		str[0] = '-';
		nb2 = -nb2;
	}
	str[size] = '\0';
	if (nb2 == 0)
		str[0] = '0';
	while (size > 0 && nb2 > 0)
	{
		str[size - 1 + (nb2 == 0 && n < 0)] = (nb2 % 10) + '0';
		nb2 = nb2 / 10;
		size --;
	}
	return (str);
}

// int	main(void)
// {
// 	char	*str_num;

// 	str_num = ft_itoa(0);
// 	printf("Chaîne : %s\n", str_num);
// 	free(str_num);
// 	return (0);
// }
