/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:41:35 by jerem             #+#    #+#             */
/*   Updated: 2024/02/08 10:41:35 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	printf ("\n\nle nombre de caractere est %ld\n\n", ft_strlen("hello world"));
// 	return (0);
// }
