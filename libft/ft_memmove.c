/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove%.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:57:05 by jerem             #+#    #+#             */
/*   Updated: 2024/02/09 17:57:05 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ptr_dst;
	char	*ptr_src;
	size_t	i;

	i = 0;
	if (!src || !dst)
		return (NULL);
	ptr_dst = (char *)dst;
	ptr_src = (char *)src;
	if (ptr_dst > ptr_src)
	{
		while (len--)
			ptr_dst[len] = ptr_src[len];
	}
	if (ptr_dst < ptr_src)
	{
		while (i < len)
		{
			ptr_dst[i] = ptr_src[i];
			i++;
		}
	}
	return (ptr_dst);
}

// int main(void) 
// {
//     char src[] = "Hello, world!";
//     char dst[20];

// printf("Source string: %s\n", src);
// printf("Dest string before copying: %s\n", dst);
// ft_memmove(dst, src, strlen(src) + 1);
// printf("Copied string by ft_memmove: %s\n", dst);
// 	printf("Source string: %s\n", src);
//     printf("Dest string before copying: %s\n", dst);
//     memmove(dst, src, strlen(src) + 1);
//     printf("Copied string by memmove: %s\n", dst);

//     return 0;
// }