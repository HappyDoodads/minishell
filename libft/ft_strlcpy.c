/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:31:37 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/19 14:50:44 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < dstsize)
	{
		ft_memcpy(dst, src, src_len + 1);
	}
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (src_len);
}

// int	main(void)
// {
// 	char	src[] = "Hello, world !";
// 	char	dst[20];
// 	size_t	len;

// 	len = ft_strlcpy(dst, src, sizeof(dst));
// 	printf("Copied string: %s\n", dst);
// 	printf("Number of characters copied: %zu\n", len);
// 	len = strlcpy(dst, src, sizeof(dst));
// 	printf("Copied string: %s\n", dst);
// 	printf("Number of characters copied: %zu\n", len);
// 	return (0);
// }
