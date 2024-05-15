/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerem <jeremy.coquet38@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:43:19 by jerem             #+#    #+#             */
/*   Updated: 2024/02/10 09:43:19 by jerem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *) s;
	if (!s)
		return (NULL);
	while (*ptr)
	{
		if (*ptr == (char)c)
			return ((char *)ptr);
		ptr++;
	}
	if (*ptr == (char)c)
		return ((char *) ptr);
	return (NULL);
}

// int	main(void)
// {
// 	printf("%s", ft_strchr("salut", 'a'));
// 	return (0);
// }
