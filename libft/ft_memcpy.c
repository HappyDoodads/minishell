/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:11:31 by jerem             #+#    #+#             */
/*   Updated: 2024/02/07 09:11:31 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *) dst;
	ptr_src = (unsigned char *) src;
	if (!dst || !src)
		return (dst);
	while (n > 0)
	{
		*(ptr_dst++) = *(ptr_src++);
		n--;
	}
	return (dst);
}

// int	main(void)
// {
// 	char	src[] = "Hello, world!";
// 	char	dest[50];

// 	ft_memcpy(dest, src, sizeof(src));
// 	printf("Source: %s\n", src);
// 	printf("Destination: %s\n", dest);
//     return (0);
// }
