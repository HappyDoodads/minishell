/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:29:54 by jcoquet           #+#    #+#             */
/*   Updated: 2024/02/15 16:02:28 by jcoquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// int	main(void)
// {
// 	char	*str;
// 	char	*ptr;

// 	str = ft_calloc(6, 2);
// 	if (!str)
// 		return (0);
// 	ptr = str;
// 	while (*str)
// 	{
// 		write(1, str, 1);
// 		str++;
// 	}
// 	free(ptr);
// 	return (0);
// }
