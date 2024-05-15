/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr%.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:54:35 by jerem             #+#    #+#             */
/*   Updated: 2024/02/09 17:54:35 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c2;
	size_t			i;

	str = (unsigned char *)s;
	c2 = (unsigned char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (i < n)
	{
		if (str[i] == c2)
		{
			return ((void *)&str[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str;
// 	int			c;
// 	size_t		n;
// 	void		*result;

// 	n = 25;
// 	str = "Hello, world!";
// 	c = 'H';
// 	result = ft_memchr(str, c, n);
// 	if (result != NULL)
// 		printf("Le caractère '%c' a été trouvé à l'adresse : %p\n", c, result);
// 	else
// 		printf("Le caractère '%c' n'a pas été trouvé dans la chaîne.\n", c);
// 	return (0);
// }
