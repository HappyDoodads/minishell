/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp%.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:54:40 by jerem             #+#    #+#             */
/*   Updated: 2024/02/09 17:54:40 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*ptr_s1;
	unsigned const char	*ptr_s2;

	ptr_s1 = (unsigned const char *) s1;
	ptr_s2 = (unsigned const char *) s2;
	if (!ptr_s1 || !ptr_s2)
		return (0);
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*ptr_s1 != *ptr_s2)
			return (*ptr_s1 - *ptr_s2);
		ptr_s1++;
		ptr_s2++;
	}
	return (0);
}

// int	main(void)
// {
// 	char str1[] = "Hello";
// 	char str2[] = "Hella";
// 	int result = ft_memcmp(str1, str2, 5);
// 		printf("Comparison result: %d\n", result);
// 	return (0);
// }