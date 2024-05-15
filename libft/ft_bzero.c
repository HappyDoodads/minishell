/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:40:53 by jerem             #+#    #+#             */
/*   Updated: 2024/02/07 08:40:53 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = s;
	i = 0;
	if (!s)
		return ;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	char s[10];
// 	size_t n = 10;
// 	size_t i = 0;
// 	ft_bzero(s, n);
// 	while (i < n)
// 	{
// 		printf("%d", s[i]);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }
