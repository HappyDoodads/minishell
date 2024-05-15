/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:50:23 by jerem             #+#    #+#             */
/*   Updated: 2024/02/07 07:50:23 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	if (!b)
		return (NULL);
	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	char	b[11];
// 	int c = 'c';
// 	size_t	len = 10;
// 	size_t	i = 0;
// 	memset (b, c, len);
// 	printf("%s", b);
// 	printf("\n");
// 	ft_memset (b, c, len);
// 	printf("%s", b);
// 	printf("\n");
// 	return (0);
// }
